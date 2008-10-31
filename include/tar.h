/* $Id$ */
/* Copyright (c) 2008 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. */



#ifndef LIBC_TAR_H
# define LIBC_TAR_H


/* constants */
/* general */
# define TMAGIC		"ustar"
# define TMAGLEN	6
# define TVERSION	"00"
# define TVERSLEN	2

/* typeflag */
# define REGTYPE	'0'
# define AREGTYPE	'\0'
# define LNKTYPE	'1'
# define SYMTYPE	'2'
# define CHRTYPE	'3'
# define BLKTYPE	'4'
# define DIRTYPE	'5'
# define FIFOTYPE	'6'
# define CONTTYPE	'7'

/* mode */
# define TSUID		04000
# define TSGID		02000
# define TSVTX		01000
# define TUREAD		00400
# define TUWRITE	00200
# define TUEXEC		00100
# define TGREAD		00040
# define TGWRITE	00020
# define TGEXEC		00010
# define TOREAD		00004
# define TOWRITE	00002
# define TOEXEC		00001

#endif /* !LIBC_TAR_H */
