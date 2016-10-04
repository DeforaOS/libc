#!/bin/sh
#$Id$
#Copyright (c) 2016 Pierre Pronchery <khorben@defora.org>
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
PROGNAME="cross.sh"
TARGETS="all"
UNAME=$(uname -s)
#executables
GCC="gcc"
MAKE="make"
MKTEMP="mktemp"
RM="rm -f"


#functions
#cross
_cross()
{
	[ $# -ge 1 -a $# -le 2 ]				|| return 1
	cppflags="-U__${UNAME}__ -D__${1}__"
	make="$MAKE CPPFLAGS=\"$cppflags\""
	[ $# -eq 2 ] && make="$make CC=\"$2\""
	objdir=$($MKTEMP -d)
	[ $? -eq 0 ]						|| return 2

	(cd .. && sh -c "$make OBJDIR='$objdir/' $TARGETS")
	ret=$?
	[ $ret -eq 0 ] || echo "$PROGNAME: $1: Could not cross-build" 1>&2
	$RM -r -- "$objdir"
	return $ret
}


#cross_all
_cross_all()
{
	for system in FreeBSD linux NetBSD OpenBSD; do
		_cross "$system" "$@"				|| return 2
	done
}


#main
_cross_all							|| return 2
case $(uname -m) in
	amd64|sparc64|x86_64)
		_cross_all "gcc -m32"
		;;
esac
