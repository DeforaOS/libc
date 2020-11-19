#!/bin/sh
#$Id$
#Copyright (c) 2017-2020 Pierre Pronchery <khorben@defora.org>
#
#Redistribution and use in source and binary forms, with or without
#modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
#
#THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
#FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
#DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
#SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
#CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
#OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.



#variables
CONFIGSH="${0%/fixme.sh}/../config.sh"
PROGNAME="fixme.sh"
PROJECTCONF="../project.conf"
REGEXP_ERROR="FIXME"
REGEXP_WARNING="\\(TODO\|XXX\\)"
#executables
DATE="date"
DEBUG="_debug"
FIND="find"
GREP="grep"
HEAD="head"
MKDIR="mkdir -p"
SORT="sort -n"
TR="tr"

[ -f "$CONFIGSH" ] && . "$CONFIGSH"


#functions
#fixme
_fixme()
{
	res=0
	subdirs=

	$DATE
	echo
	while read line; do
		case "$line" in
			"["*)
				break
				;;
			"subdirs="*)
				subdirs=${line#subdirs=}
				subdirs=$(echo "$subdirs" | $TR ',' ' ')
				;;
		esac
	done < "$PROJECTCONF"
	if [ ! -n "$subdirs" ]; then
		_error "Could not locate directories to analyze"
		return $?
	fi
	for subdir in $subdirs; do
		[ -d "../$subdir" ] || continue
		for filename in $($FIND "../$subdir" -type f | $SORT); do
			callback=$(_fixme_callback "$filename")
			[ -n "$callback" ] || continue
			($callback "$filename") 2>&1
			if [ $? -ne 0 ]; then
				echo "$PROGNAME: $filename: FAIL" 1>&2
				res=2
			fi
		done
	done
	return $res
}

_fixme_callback()
{
	filename="$1"
	ext=${filename##*/}
	ext=${ext%.in}
	ext=${ext##*.}
	callback=

	case "$ext" in
		asm|S)
			echo "_fixme_callback_asm"
			return 0
			;;
		c|cc|cpp|cxx|h|js|v)
			echo "_fixme_callback_c"
			return 0
			;;
		conf|sh)
			echo "_fixme_callback_sh"
			return 0
			;;
		py)
			echo "_fixme_callback_python"
			return 0
			;;
		htm|html|xml|xsl)
			echo "_fixme_callback_xml"
			return 0
			;;
	esac
	case $($HEAD -n 1 "$filename") in
		"#!/bin/sh"*|"#! /bin/sh"*|\
		"#!/usr/bin/env bash"*|"#! /usr/bin/env bash"*)
			echo "_fixme_callback_sh"
			return 0
			;;
		"#!/usr/bin/env python"*|"#! /usr/bin/env python"*)
			echo "_fixme_callback_python"
			return 0
			;;
		"<html"*|"<?xml"*)
			echo "_fixme_callback_xml"
			return 0
			;;
	esac
	return 2
}

_fixme_callback_asm()
{
	res=0
	filename="$1"

	#warnings
	$GREP -nH "/\\*.*$REGEXP_WARNING" "$filename"
	#failures
	$GREP -nH "/\\*.*$REGEXP_ERROR" "$filename" && res=2
	return $res
}

_fixme_callback_c()
{
	res=0
	filename="$1"

	#warnings
	$GREP -nH "/\\(/\\|\\*\\).*$REGEXP_WARNING" "$filename"
	#failures
	$GREP -nH "/\\(/\\|\\*\\).*$REGEXP_ERROR" "$filename" && res=2
	return $res
}

_fixme_callback_python()
{
	res=0
	filename="$1"
	comment="#"

	#warnings
	$GREP -nH "$comment.*$REGEXP_WARNING" "$filename"
	#failures
	$GREP -nH "$comment.*$REGEXP_ERROR" "$filename" && res=2
	return $res
}

_fixme_callback_sh()
{
	res=0
	filename="$1"
	comment="#"

	#warnings
	$GREP -nH "$comment.*$REGEXP_WARNING" "$filename"
	#failures
	$GREP -nH "$comment.*$REGEXP_ERROR" "$filename" && res=2
	return $res
}

_fixme_callback_xml()
{
	res=0
	filename="$1"

	#XXX limited to a single line
	#warnings
	$GREP -nH "<!--.*$REGEXP_WARNING" "$filename"
	#failures
	$GREP -nH "<!--.*$REGEXP_ERROR" "$filename" && res=2
	return $res
}


#debug
_debug()
{
	echo "$@" 1>&3
	"$@"
	res=$?
	#ignore errors when the command is not available
	[ $res -eq 127 ]					&& return 0
	return $res
}


#error
_error()
{
	echo "$PROGNAME: $@" 1>&2
	return 2
}


#usage
_usage()
{
	echo "Usage: $PROGNAME [-c] target..." 1>&2
	return 1
}


#main
clean=0
while getopts "cO:P:" name; do
	case "$name" in
		c)
			clean=1
			;;
		O)
			export "${OPTARG%%=*}"="${OPTARG#*=}"
			;;
		P)
			#XXX ignored for compatibility
			;;
		?)
			_usage
			exit $?
			;;
	esac
done
shift $((OPTIND - 1))
if [ $# -lt 1 ]; then
	_usage
	exit $?
fi

#clean
[ $clean -ne 0 ] && exit 0

exec 3>&1
ret=0
while [ $# -gt 0 ]; do
	target="$1"
	dirname="${target%/*}"
	shift

	if [ -n "$dirname" -a "$dirname" != "$target" ]; then
		$MKDIR -- "$dirname"				|| ret=$?
	fi
	_fixme > "$target"					|| ret=$?
done
exit $ret
