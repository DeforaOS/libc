#!/bin/sh
#$Id$
#Copyright (c) 2012-2015 Pierre Pronchery <khorben@defora.org>
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
[ -n "$OBJDIR" ] || OBJDIR="./"
SYSTEM="$(uname -s)"
SOEXT="so"
#XXX not tested
[ "$SYSTEM" = "Darwin" ] && SOEXT="dylib"
#executables
DATE="date"


#functions
#fail
_fail()
{
	test="$1"

	shift
	echo -n "$test:" 1>&2
	(echo
	echo "Testing: $OBJDIR$test" "$@"
	"$OBJDIR$test" "$@") >> "$target" 2>&1
	res=$?
	if [ $res -ne 0 ]; then
		echo " FAIL (error $res)" 1>&2
	else
		echo " PASS" 1>&2
	fi
}


#test
_test()
{
	test="$1"

	shift
	echo -n "$test:" 1>&2
	(echo
	echo "Testing: $OBJDIR$test" "$@"
	"$OBJDIR$test" "$@") >> "$target" 2>&1
	res=$?
	if [ $res -ne 0 ]; then
		echo " FAIL" 1>&2
		FAILED="$FAILED $test(error $res)"
		return 2
	else
		echo " PASS" 1>&2
		return 0
	fi
}


#usage
_usage()
{
	echo "Usage: tests.sh [-c][-P prefix]" 1>&2
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

[ "$clean" -ne 0 ]			&& exit 0

$DATE > "$target"
FAILED=
echo "Performing tests:" 1>&2
_test "errno"
_test "fnmatch"
_test "includes"
_test "langinfo"
_test "netdb"
_test "ptrace"
_test "pwd"
_test "regex"
_test "rt"
_test "select"
_test "setjmp"
_test "signal"
_test "socket"
_test "start" argv1 argv2
_test "stdarg"
_test "stdint"
_test "stdio"
_test "string"
_test "time"
_test "unistd"
echo "Expected failures:" 1>&2
_fail "dlfcn" "../src/libc.$SOEXT"
_fail "stdlib"
if [ -n "$FAILED" ]; then
	echo "Failed tests:$FAILED" 1>&2
	exit 2
fi
echo "All tests completed" 1>&2
