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
CONFIGSH="${0%/ldso.sh}/../config.sh"
LDSO=
PREFIX="/usr/local"
[ -f "$CONFIGSH" ] && . "$CONFIGSH"
PROGNAME="ldso.sh"
SYSTEM=$(uname -s)
#executables
DEBUG="_debug"
DEVNULL="/dev/null"
INSTALL="install"
LN="ln -f"
MKDIR="mkdir -m 0755 -p"
RM="rm -f"


#functions
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

#detect ld.so
[ -n "$LDSO" ] || case "$SYSTEM" in
	FreeBSD)
		LDSO="/libexec/ld-elf.so.1"
		;;
	Linux)
		LDSO="/lib/ld-linux-$(uname -p).so.2"
		;;
	NetBSD)
		LDSO="/libexec/ld.elf_so"
		;;
esac
#XXX ignore errors
if [ -z "$LDSO" ]; then
	_error "$SYSTEM: No known dynamic linker for this platform"
	exit 0
elif [ ! -f "$LDSO" ]; then
	_error "$LDSO: Dynamic linker not found"
	exit 0
fi

#clean
[ "$clean" -ne 0 ] && exit 0

#do not tamper with the underlying system
[ -z "$DESTDIR" ] && exit 0

#uninstall
if [ "$uninstall" -eq 1 ]; then
	$DEBUG $RM -- "$PREFIX/${LDSO##*/}" "$PREFIX/ld.so"	|| exit 2
	exit 0
fi

#install
if [ "$install" -eq 1 ]; then
	($DEBUG $MKDIR -- "$PREFIX" &&
	$DEBUG $INSTALL -m 0755 "$LDSO" "$PREFIX/${LDSO##*/}")	|| exit 2
	if [ "${LDSO##*/}" != "ld.so" ]; then
		$DEBUG $LN -s "${LDSO##*/}" "$PREFIX/ld.so"	|| exit 2
	fi
fi
