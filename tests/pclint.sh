#!/bin/sh
#$Id$
#Copyright (c) 2014-2025 Pierre Pronchery <khorben@defora.org>
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
CONFIGSH="${0%/pclint.sh}/../config.sh"
PROGNAME="pclint.sh"
PROJECTCONF="../project.conf"
#executables
DATE="date"
DEBUG="_debug"
ECHO="/bin/echo"
FIND="find"
MKDIR="mkdir -p"
PCLINT="pkgconf --validate"
SORT="sort -n"
TR="tr"

[ -f "$CONFIGSH" ] && . "$CONFIGSH"


#functions
#pclint
_pclint()
{
	res=0
	subdirs=

	$DATE
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
		while read filename; do
			[ -n "$filename" ] || continue
			echo
			$ECHO -n "$filename:"
			_pclint_file "$filename"
			if [ $? -eq 0 ]; then
				echo " OK"
				echo "$PROGNAME: $filename: OK" 1>&2
			else
				echo "FAIL"
				echo "$PROGNAME: $filename: FAIL" 1>&2
				res=2
			fi
		done << EOF
$($FIND "../$subdir" -type f -a -iname '*.pc' | $SORT)
EOF
	done
	return $res
}

_pclint_file()
{
	$DEBUG $PCLINT "$filename" 2>&1				|| return 2
	#try to detect invalid use of return
	#XXX this test is not accurate (therefore a warning)
	warn=0
	while read line; do
		case "$line" in
			*return*)
				warn=1
				;;
			*)
				warn=0
				;;
		esac
	done < "$filename"
	if [ $warn -ne 0 ]; then
		_error "$filename: return instead of exit in the global scope"
	fi
	return 0
}


#debug
_debug()
{
	echo "$@" 1>&3
	"$@"
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
	_pclint > "$target"					|| ret=$?
done
exit $ret
