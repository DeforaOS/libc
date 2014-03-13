#!/bin/sh
#$Id$
#Copyright (c) 2012-2014 Pierre Pronchery <khorben@defora.org>
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
PREFIX="/usr/local"
[ -f "../config.sh" ] && . "../config.sh"
#executables
DEBUG="_debug"
GTKDOC_FIXXREF="gtkdoc-fixxref"
GTKDOC_MKDB="gtkdoc-mkdb"
GTKDOC_MKHTML="gtkdoc-mkhtml"
GTKDOC_MKTMPL="gtkdoc-mktmpl"
GTKDOC_SCAN="gtkdoc-scan"
INSTALL="install -m 0644"
MKDIR="mkdir -m 0755 -p"
RM="rm -f"
TOUCH="touch"


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
	echo "gtkdoc.sh: $@" 1>&2
	return 2
}


#usage
_usage()
{
	echo "Usage: gtkdoc.sh [-c|-i|-u][-P prefix] target..." 1>&2
	return 1
}


#main
clean=0
install=0
uninstall=0
while getopts "ciuP:" name; do
	case "$name" in
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
shift $((OPTIND - 1))
if [ $# -eq 0 ]; then
	_usage
	exit $?
fi

#check the variables
if [ -z "$PACKAGE" ]; then
	_error "The PACKAGE variable needs to be set"
	exit $?
fi
MODULE="$PACKAGE"

[ -z "$DATADIR" ] && DATADIR="$PREFIX/share"
instdir="$DATADIR/gtk-doc/html"

while [ $# -gt 0 ]; do
	target="$1"
	shift

	#clean
	[ "$clean" -ne 0 ] && continue

	#uninstall
	if [ "$uninstall" -eq 1 ]; then
		for i in gtkdoc/html/*.*; do
			[ -f "$i" ] || continue
			file="${i##*/}"
			$DEBUG $RM "$instdir/$MODULE/$file"	|| exit 2
		done
		continue
	fi

	#create
	case "$target" in
		gtkdoc/html.stamp)
			$MKDIR "gtkdoc/html" &&
			(cd "gtkdoc/html" &&
				$DEBUG $GTKDOC_MKHTML "$MODULE" \
					"../$MODULE-docs.xml") &&
			(cd "gtkdoc" &&
				$DEBUG $GTKDOC_FIXXREF \
					--module="$MODULE" \
					--module-dir="html" \
					--html-dir="$instdir")
			;;
		gtkdoc/sgml.stamp)
			(cd "gtkdoc" &&
				$DEBUG $GTKDOC_MKDB \
					--module="$MODULE" \
					--output-dir="xml" \
					--output-format="xml" \
					--tmpl-dir="tmpl")
			;;
		gtkdoc/tmpl.stamp)
			(cd "gtkdoc" &&
				$DEBUG $GTKDOC_MKTMPL \
					--module="$MODULE" \
					--output-dir="tmpl")
			;;
		gtkdoc/*.types)
			(cd ".." &&
				$DEBUG $GTKDOC_SCAN \
					--module="$MODULE" \
					--source-dir="include" \
					--output-dir="doc/gtkdoc")
			;;
		*)
			echo "$0: $target: Unknown type" 1>&2
			exit 2
			;;
	esac
	#XXX ignore errors
	if [ $? -ne 0 ]; then
		echo "$0: $target: Could not create documentation" 1>&2
		install=0
	fi
	$TOUCH "$target"

	#install
	if [ "$install" -eq 1 ]; then
		$DEBUG $MKDIR "$instdir/$MODULE"		|| exit 2
		for i in gtkdoc/html/*.*; do
			[ -f "$i" ] || continue
			file="${i##*/}"
			$DEBUG $INSTALL "$i" "$instdir/$MODULE/$file" \
								|| exit 2
		done
	fi
done
