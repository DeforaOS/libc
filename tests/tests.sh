#!/usr/bin/env sh
#$Id$
#Copyright (c) 2012 Pierre Pronchery <khorben@defora.org>
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


#functions
#usage
_usage()
{
	echo "Usage: tests.sh" 1>&2
	return 1
}


#main
while getopts "P:" "name"; do
	case "$name" in
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

> "$target"
FAILED=
./dlfcn "../src/libc.so">> "$target"	|| FAILED="$FAILED dlfcn(error $?)"
./includes		>> "$target"	|| FAILED="$FAILED includes(error $?)"
./ptrace		>> "$target"	|| FAILED="$FAILED ptrace(error $?)"
./regex			>> "$target"	|| FAILED="$FAILED regex(error $?)"
./select		>> "$target"	|| FAILED="$FAILED select(error $?)"
./setjmp		>> "$target"	|| FAILED="$FAILED setjmp(error $?)"
./signal		>> "$target"	|| FAILED="$FAILED signal(error $?)"
./socket		>> "$target"	|| FAILED="$FAILED socket(error $?)"
./start argv1 argv2	>> "$target"	|| FAILED="$FAILED start(error $?)"
./stdint		>> "$target"	|| FAILED="$FAILED stdint(error $?)"
./stdio			>> "$target"	|| FAILED="$FAILED stdio(error $?)"
./string		>> "$target"	|| FAILED="$FAILED string(error $?)"
./time			>> "$target"	|| FAILED="$FAILED time(error $?)"
[ -z "$FAILED" ]			&& exit 0
echo "Failed tests:$FAILED" 1>&2
exit 2
