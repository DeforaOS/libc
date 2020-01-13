#!/bin/sh
#$Id$
#Copyright (c) 2012-2020 Pierre Pronchery <khorben@defora.org>
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
PROGNAME="gtkdoc.sh"
#executables
CP="cp"
DEBUG="_debug"
GTKDOC_FIXXREF="gtkdoc-fixxref"
GTKDOC_MKDB="gtkdoc-mkdb"
GTKDOC_MKHTML="gtkdoc-mkhtml"
GTKDOC_MKTMPL="gtkdoc-mktmpl"
GTKDOC_SCAN="gtkdoc-scan"
INSTALL="install -m 0644"
MKDIR="mkdir -m 0755 -p"
RM="rm -f"
RMDIR="rmdir"
TOUCH="touch"

[ -f "../config.sh" ] && . "../config.sh"


#functions
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


#gtkdoc_mkdb
_gtkdoc_mkdb()
{
	module="$1"
	sourcedir="$2"
	outputdir="$3"

	(cd "$sourcedir" &&
		$DEBUG $GTKDOC_MKDB --module="$module" \
				--output-dir="$outputdir" \
				--output-format="xml" --tmpl-dir="tmpl")
}


#gtkdoc_mktmpl
_gtkdoc_mktmpl()
{
	module="$1"
	sourcedir="$2"
	outputdir="$3"

	(cd "$sourcedir" &&
		$DEBUG $GTKDOC_MKTMPL --module="$module" \
				--output-dir="$outputdir")
}


#gtkdoc_scan
_gtkdoc_scan()
{
	module="$1"
	sourcedir="$2"
	outputdir="$3"

	(cd ".." &&
		$DEBUG $GTKDOC_SCAN --module="$module" \
				--source-dir="$sourcedir" \
				--output-dir="$outputdir")
#		--rebuild-types
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
while getopts "ciO:uP:" name; do
	case "$name" in
		c)
			clean=1
			;;
		i)
			uninstall=0
			install=1
			;;
		O)
			export "${OPTARG%%=*}"="${OPTARG#*=}"
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
if [ $# -lt 1 ]; then
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

exec 3>&1
while [ $# -gt 0 ]; do
	target="$1"
	target="${target#$OBJDIR}"
	shift

	#clean
	[ "$clean" -ne 0 ] && continue

	#uninstall
	if [ "$uninstall" -eq 1 ]; then
		for i in "${OBJDIR}gtkdoc/html/"*.*; do
			[ -f "$i" ] || continue
			file="${i##*/}"
			$DEBUG $RM -- "$instdir/$MODULE/$file"	|| exit 2
		done
		if [ -d "$instdir/$MODULE" ]; then
			$DEBUG $RMDIR -- "$instdir/$MODULE"	|| exit 2
		fi
		continue
	fi

	#create
	case "$target" in
		gtkdoc/html.stamp)
			output="${OBJDIR}gtkdoc/html"
			$DEBUG $MKDIR -- "$output"		|| exit 2
			driver="$MODULE-docs.xml"
			if [ -n "$OBJDIR" ]; then
				$DEBUG $CP -- "gtkdoc/$driver" "${OBJDIR}gtkdoc" \
								|| exit 2
			fi
			(cd "$output" &&
				$DEBUG $GTKDOC_MKHTML "$MODULE" \
					"../$driver")
			#detect when gtk-doc is not available
			res=$?
			if [ $res -eq 127 ]; then
				_error "$GTKDOC_MKHTML: Not available" \
					"(not generating documentation)"
				continue
			elif [ $res -ne 0 ]; then
				exit 2
			fi
			output="${OBJDIR}gtkdoc"
			(cd "$output" &&
				$DEBUG $GTKDOC_FIXXREF \
					--module="$MODULE" \
					--module-dir="html" \
					--html-dir="$instdir")	|| exit 2
			;;
		gtkdoc/tmpl.stamp)
			output="tmpl"
			if [ -n "$OBJDIR" ]; then
				output="${OBJDIR}gtkdoc/tmpl"
				$DEBUG $MKDIR -- "$output"	|| exit 2
			fi
			_gtkdoc_mktmpl "$MODULE" "${OBJDIR}gtkdoc" "$output"
			;;
		gtkdoc/xml.stamp)
			output="xml"
			if [ -n "$OBJDIR" ]; then
				output="${OBJDIR}gtkdoc"
				sections="gtkdoc/$MODULE-sections.txt"
				$DEBUG $MKDIR -- "$output/xml"	|| exit 2
				$DEBUG $CP -- "$sections" "$output" \
								|| exit 2
				_gtkdoc_scan "$MODULE" "include" "$output"
				output="${OBJDIR}gtkdoc/xml"
			fi
			_gtkdoc_mkdb "$MODULE" "${OBJDIR}gtkdoc" "$output"
			;;
		gtkdoc/*.types)
			output="$PWD/gtkdoc"			|| exit 2
			if [ -n "$OBJDIR" ]; then
				output="${OBJDIR}gtkdoc"
				$DEBUG $MKDIR -- "$output"	|| exit 2
			fi
			_gtkdoc_scan "$MODULE" "include" "$output"
			;;
		*)
			_error "$target: Unknown type"
			exit $?
			;;
	esac
	#XXX ignore errors
	if [ $? -ne 0 ]; then
		_error "$target: Could not create documentation"
		install=0
	fi
	$TOUCH "${OBJDIR}$target"

	#install
	if [ "$install" -eq 1 ]; then
		$DEBUG $MKDIR "$instdir/$MODULE"		|| exit 2
		for i in "${OBJDIR}gtkdoc/html/"*.*; do
			[ -f "$i" ] || continue
			file="${i##*/}"
			$DEBUG $INSTALL "$i" "$instdir/$MODULE/$file" \
								|| exit 2
		done
	fi
done
