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
PROGNAME="fixme.sh"
PROJECTCONF="../project.conf"
#executables
DATE="date"
DEBUG="_debug"
FIND="find"
GREP="grep"
MKDIR="mkdir -p"
SORT="sort -n"
TR="tr"


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
			callback=
			ext=${filename##*/}
			ext=${ext%.in}
			ext=${ext##*.}
			case "$ext" in
				asm|S)
					callback="_fixme_asm"
					;;
				c|cc|cpp|cxx|h|js)
					callback="_fixme_c"
					;;
				conf|sh)
					callback="_fixme_sh"
					;;
				htm|html|xml)
					callback="_fixme_xml"
					;;
			esac
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

_fixme_asm()
{
	res=0
	filename="$1"

	#warnings
	$GREP -nH '/\*.*\(TODO\|XXX\)' "$filename"
	#failures
	$GREP -nH '/\*.*FIXME' "$filename" && res=2
	return $res
}

_fixme_c()
{
	res=0
	filename="$1"

	#warnings
	$GREP -nH '/\(/\|\*\).*\(TODO\|XXX\)' "$filename"
	#failures
	$GREP -nH '/\(/\|\*\).*FIXME' "$filename" && res=2
	return $res
}

_fixme_sh()
{
	res=0
	filename="$1"
	#XXX avoid matching the regexp
	comment="#"

	#warnings
	$GREP -nH "$comment.*\\(TODO\\|XXX\\)" "$filename"
	#failures
	$GREP -nH "$comment.*FIXME" "$filename" && res=2
	return $res
}

_fixme_xml()
{
	res=0
	filename="$1"

	#XXX limited to a single line
	#warnings
	$GREP -nH '<!--.*\(TODO\|XXX\)' "$filename"
	#failures
	$GREP -nH '<!--.*FIXME' "$filename" && res=2
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
