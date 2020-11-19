#!/bin/sh
#$Id$
#Copyright (c) 2018-2020 Pierre Pronchery <khorben@defora.org>
#This file is part of DeforaOS System libSystem
#All rights reserved.
#
#Redistribution and use in source and binary forms, with or without
#modification, are permitted provided that the following conditions are
#met:
#
#1. Redistributions of source code must retain the above copyright
#   notice, this list of conditions and the following disclaimer.
#
#2. Redistributions in binary form must reproduce the above copyright
#   notice, this list of conditions and the following disclaimer in the
#   documentation and/or other materials provided with the distribution.
#
#THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
#IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
#TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
#PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
#HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
#SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
#TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
#PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
#LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
#NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
#SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.



#variables
CONFIGSH="${0%/coverage.sh}/../config.sh"
CFLAGS=
LDFLAGS=
PROGNAME="coverage.sh"
TARGET="tests.log"
#executables
CC="gcc -fprofile-arcs -ftest-coverage"
DATE="date"
FIND="find"
GCOV="gcov"
[ -n "$MAKE" ] || MAKE="make"
MKDIR="mkdir -p"
MKTEMP="mktemp"
RM="rm -f"

[ -f "$CONFIGSH" ] && . "$CONFIGSH"


#coverage
_coverage()
{
	#create a temporary directory
	tmpdir=$($MKTEMP -d)
	if [ $? -ne 0 ]; then
		return 2
	fi
	#build the project in a separate directory
	for dir in src tools; do
		[ -d "../$dir" ] || continue
		$MKDIR "$tmpdir/$dir" &&
		(cd "../$dir" && $MAKE CC="$CC" CFLAGS="$CFLAGS" LDFLAGS="$LDFLAGS" OBJDIR="$tmpdir/$dir/") || break
	done &&
	$MKDIR "$tmpdir/tests" &&
	$MAKE CC="$CC" CFLAGS="$CFLAGS" LDFLAGS="$LDFLAGS" OBJDIR="$tmpdir/tests/" "$tmpdir/tests/$TARGET"
	res=$?
	unset dir
	#look for any code executed
	$FIND "$tmpdir" -name '*.gcda' | while read filename; do
		echo
		echo "${filename%.gcda}.c:"
		$GCOV -n "${filename%.gcda}.gcno"
		#TODO output the GCOV file
	done
	$RM -r -- "$tmpdir"
	return $res
}


#date
_date()
{
	if [ -n "$SOURCE_DATE_EPOCH" ]; then
		TZ=UTC $DATE -d "@$SOURCE_DATE_EPOCH" '+%a %b %d %T %Z %Y'
	else
		$DATE
	fi
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
			#XXX ignored
			;;
		?)
			_usage
			exit $?
			;;
	esac
done
shift $((OPTIND - 1))
if [ $# -eq 0 ]; then
	_usage
	exit $?
fi

while [ $# -ne 0 ]; do
	target="$1"
	shift

	[ "$clean" -eq 0 ]					|| break

	(_date; echo) > "$target"
	echo "Gathering test coverage:" 1>&2
	_coverage >> "$target" || exit 2
	echo "Gathered test coverage" 1>&2
done
exit 0
