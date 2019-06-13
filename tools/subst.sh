#!/bin/sh
#$Id$
#Copyright (c) 2012-2019 Pierre Pronchery <khorben@defora.org>
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
CONFIGSH="${0%/subst.sh}/../config.sh"
PREFIX="/usr/local"
BINDIR=
DATADIR=
INCLUDEDIR=
LDSO=
LIBDIR=
LIBEXECDIR=
MANDIR=
PROGNAME="subst.sh"
SYSCONFDIR=
#executables
CHMOD="chmod"
DATE="date"
DEBUG="_debug"
DEVNULL="/dev/null"
INSTALL="install"
MKDIR="mkdir -m 0755 -p"
RM="rm -f"
SED="sed"
[ -f "$CONFIGSH" ] && . "$CONFIGSH"


#functions
#subst
_subst()
{
	#check the variables
	if [ -z "$PACKAGE" ]; then
		_error "The PACKAGE variable needs to be set"
		return $?
	fi
	if [ -z "$VERSION" ]; then
		_error "The VERSION variable needs to be set"
		return $?
	fi
	[ -z "$BINDIR" ] && BINDIR="$PREFIX/bin"
	[ -z "$DATADIR" ] && DATADIR="$PREFIX/share"
	[ -z "$INCLUDEDIR" ] && INCLUDEDIR="$PREFIX/include"
	if [ -z "$LDSO" ]; then
		case "$(uname -s)" in
			FreeBSD)
				LDSO="/libexec/ld-elf.so.1"
			;;
			Linux)
				LDSO="/lib/ld-linux-$(uname -m | tr _ -).so.2"
				;;
			*)
				LDSO="/libexec/ld.elf_so"
				;;
		esac
	fi
	[ -z "$LIBDIR" ] && LIBDIR="$PREFIX/lib"
	[ -z "$LIBEXECDIR" ] && LIBEXECDIR="$PREFIX/libexec"
	[ -z "$MANDIR" ] && MANDIR="$DATADIR/man"
	if [ -z "$SYSCONFDIR" ]; then
		SYSCONFDIR="$PREFIX/etc"
		[ "$PREFIX" = "/usr" ] && SYSCONFDIR="/etc"
	fi

	while [ $# -gt 0 ]; do
		target="$1"
		shift

		#clean
		[ "$clean" -ne 0 ] && continue

		#uninstall
		if [ "$uninstall" -eq 1 ]; then
			$DEBUG $RM -- "$PREFIX/$target"		|| return 2
			continue
		fi

		#install
		if [ "$install" -eq 1 ]; then
			source="${target#$OBJDIR}"
			$DEBUG $MKDIR -- "$PREFIX"		|| return 2
			mode="-m 0644"
			[ -x "${source}.in" ] && mode="-m 0755"
			$DEBUG $INSTALL $mode "$target" "$PREFIX/$source" \
								|| return 2
			continue
		fi

		#create
		source="${target#$OBJDIR}"
		source="${source}.in"
		([ -z "$OBJDIR" ] || $DEBUG $MKDIR -- "${target%/*}") \
								|| return 2
		$DEBUG $SED -e "s;@PACKAGE@;$PACKAGE;g" \
			-e "s;@VERSION@;$VERSION;g" \
			-e "s;@PREFIX@;$PREFIX;g" \
			-e "s;@BINDIR@;$BINDIR;g" \
			-e "s;@DATADIR@;$DATADIR;g" \
			-e "s;@DATE@;$DATE;g" \
			-e "s;@INCLUDEDIR@;$INCLUDEDIR;g" \
			-e "s;@LDSO@;$LDSO;g" \
			-e "s;@LIBDIR@;$LIBDIR;g" \
			-e "s;@LIBEXECDIR@;$LIBEXECDIR;g" \
			-e "s;@MANDIR@;$MANDIR;g" \
			-e "s;@PWD@;$PWD;g" \
			-e "s;@SYSCONFDIR@;$SYSCONFDIR;g" \
			-- "$source" > "$target"
		if [ $? -ne 0 ]; then
			$RM -- "$target" 2> "$DEVNULL"
			return 2
		elif [ -x "$source" ]; then
			$DEBUG $CHMOD -- 0755 "$target"
		fi
	done
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
	echo "Usage: $PROGNAME [-c|-i|-u][-P prefix] target..." 1>&2
	return 1
}


#main
clean=0
install=0
uninstall=0
while getopts "ciuO:P:" name; do
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
		O)
			export "${OPTARG%%=*}"="${OPTARG#*=}"
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
if [ $# -lt 1 ]; then
	_usage
	exit $?
fi

if [ -n "$SOURCE_DATE_EPOCH" ]; then
	DATE="$($DATE -d "@$SOURCE_DATE_EPOCH" '+%B %d, %Y')"
else
	DATE="$($DATE '+%B %d, %Y')"
fi

exec 3>&1
_subst "$@"
