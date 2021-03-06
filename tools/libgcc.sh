#!/bin/sh
#$Id$
#Copyright (c) 2016 Pierre Pronchery <khorben@defora.org>
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
CONFIGSH="${0%/libgcc.sh}/../config.sh"
PREFIX="/usr/local"
[ -f "$CONFIGSH" ] && . "$CONFIGSH"
PROGNAME="libgcc.sh"
#executables
[ -z "$CC" ] && CC="cc"
DEBUG="_debug"
DEVNULL="/dev/null"
INSTALL="install"
MKDIR="mkdir -m 0755 -p"
RM="rm -f"


#functions
_libgcc()
{
	[ $# -eq 1 ]						|| return 1
	target="$1"
	mode="0644"
	[ "${target%.so}" = "$target" ] || mode="0755"

	#uninstall
	if [ "$uninstall" -eq 1 ]; then
		$DEBUG $RM -- "$PREFIX/${target##*/}"		|| return 2
		return 0
	fi

	#install
	if [ "$install" -eq 1 ]; then
		$DEBUG $MKDIR -- "$PREFIX"			|| return 2
		$DEBUG $INSTALL -m "$mode" "$target" "$PREFIX/${target##*/}" \
								|| return 2
	fi

	return 0
}


#debug
_debug()
{
	echo "$@" 1>&2
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
	echo "Usage: $PROGNAME [-c|-i|-u][-P prefix] target" 1>&2
	return 1
}


#main
clean=0
install=0
uninstall=0
while getopts "ciuP:" name; do
	case $name in
		c)
			clean=1
			;;
		i)
			uninstall=0
			install=1
			;;
		u)
			install=0
			uninstall=1
			;;
		P)
			PREFIX="$OPTARG"
			;;
		?)
			_usage
			exit $?
			;;
	esac
done
shift $(($OPTIND - 1))
if [ $# -ne 1 ]; then
	_usage
	exit $?
fi

#clean
[ "$clean" -ne 0 ] && exit 0

#do not tamper with the underlying system
[ -z "$DESTDIR" ] && exit 0

#check for libgcc.a
target=$($CC -print-libgcc-file-name)
[ $? -ne 0 -o -z "$target" ] && exit 0

_libgcc "$target"						|| exit $?

#check for libgcc_s.so
target=$($CC -print-file-name=libgcc_s.so)
if [ $? -eq 0 -a -n "$target" ]; then
	_libgcc "$target"					|| exit $?
fi
exit 0
