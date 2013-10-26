#!/usr/bin/env sh
#$Id$
#Copyright (c) 2012-2013 Pierre Pronchery <khorben@defora.org>
#This file is part of DeforaOS System libc
#This program is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, version 3 of the License.
#
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with this program.  If not, see <http://www.gnu.org/licenses/>.


#variables
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
	echo "Testing: ./$test" "$@"
	"./$test" "$@") >> "$target" 2>&1
	res=$?
	if [ $res -ne 0 ]; then
		echo " FAILED (error $res)" 1>&2
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
	echo "Testing: ./$test" "$@"
	"./$test" "$@") >> "$target" 2>&1
	res=$?
	if [ $res -ne 0 ]; then
		echo " FAILED" 1>&2
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
_test "includes"
_test "langinfo"
_test "netdb"
_test "ptrace"
_test "regex"
_test "select"
_test "setjmp"
_test "signal"
_test "socket"
_test "start" argv1 argv2
_test "stdint"
_test "stdio"
_test "string"
_test "time"
_test "unistd"
echo "Expected failures:" 1>&2
_fail "dlfcn" "../src/libc.so"
if [ -n "$FAILED" ]; then
	echo "Failed tests:$FAILED" 1>&2
	exit 2
fi
echo "All tests completed" 1>&2
