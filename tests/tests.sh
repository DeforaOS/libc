#!/bin/sh
#$Id$
#Copyright (c) 2012-2017 Pierre Pronchery <khorben@defora.org>
#This file is part of DeforaOS System libc
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
ARCH="$(uname -m)"
case "$ARCH" in
	x86_64)
		ARCH="amd64"
		;;
esac
DEVNULL="/dev/null"
[ -n "$OBJDIR" ] || OBJDIR="./"
PROGNAME="tests.sh"
SYSTEM="$(uname -s)"
SOEXT="so"
#XXX not tested
[ "$SYSTEM" = "Darwin" ] && SOEXT="dylib"
#executables
DATE="date"


#functions
#date
_date()
{
	if [ -n "$SOURCE_DATE_EPOCH" ]; then
		TZ=UTC $DATE -d "@$SOURCE_DATE_EPOCH" '+%a %b %d %T %Z %Y'
	else
		$DATE
	fi
}


#fail
_fail()
{
	_run "$@" >> "$target"
}


#run
_run()
{
	test="$1"
	sep=
	[ $# -eq 1 ] || sep=" "

	shift
	echo -n "$test:" 1>&2
	(echo
	echo "Testing: $test" "$@"
	"$OBJDIR$test" "$@") 2>&1
	res=$?
	if [ $res -ne 0 ]; then
		echo "Test: $test$sep$@: FAIL (error $res)"
		echo " FAIL" 1>&2
	else
		echo "Test: $test$sep$@: PASS"
		echo " PASS" 1>&2
	fi
	return $res
}


#test
_test()
{
	_run "$@" >> "$target"
	res=$?
	[ $res -eq 0 ] || FAILED="$FAILED $test(error $res)"
}


#usage
_usage()
{
	echo "Usage: $PROGNAME [-c][-P prefix]" 1>&2
	return 1
}


#main
clean=0
while getopts "cP:" name; do
	case "$name" in
		c)
			clean=1
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
if [ $# -ne 1 ]; then
	_usage
	exit $?
fi
target="$1"

[ "$clean" -ne 0 ]						&& exit 0

#main
if ! _run "start" argv1 argv2 > "$DEVNULL" 2>&1; then
	echo "Not performing tests (not functional)"
	exit 0
fi
_date > "$target"
FAILED=
echo "Performing tests:" 1>&2
_test "errno"
_test "fnmatch"
_test "iconv"
_test "includes"
_test "inttypes"
_test "langinfo"
_test "mman"
_test "msg"
_test "netdb"
_test "ptrace"
_test "pwd"
_test "regex"
_test "resource"
_test "rt"
_test "select"
_test "setjmp"
[ "$SYSTEM" != "FreeBSD" -a "$SYSTEM" != "Linux" ] && _test "signal"
_test "socket"
[ "$SYSTEM" != "Linux" -o "$ARCH" != "amd64" ] && _test "ssp"
_test "start" argv1 argv2
_test "stdarg"
_test "stdint"
_test "stdio"
[ "$SYSTEM" = "NetBSD" ] && _test "stdlib"
_test "string"
_test "unistd"
_test "utsname"
echo "Expected failures:" 1>&2
_fail "dlfcn" "../src/libc.$SOEXT"
[ "$SYSTEM" = "FreeBSD" -o "$SYSTEM" = "Linux" ] && _fail "signal"
[ "$SYSTEM" != "Linux" -o "$ARCH" != "amd64" ] || _fail "ssp"
[ "$SYSTEM" = "NetBSD" ] || _fail "stdlib"
_fail "time"
if [ -n "$FAILED" ]; then
	echo "Failed tests:$FAILED" 1>&2
	exit 2
fi
echo "All tests completed" 1>&2
