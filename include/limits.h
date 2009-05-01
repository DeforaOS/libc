/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_LIMITS_H
# define LIBC_LIMITS_H

# include <compat/limits.h>


/* constants */
/* runtime invariant values */
# ifndef PAGESIZE
#  define PAGESIZE 4096 /* XXX OS and architecture dependent */
# endif
# ifndef PAGE_SIZE
#  define PAGE_SIZE PAGE_SIZE
# endif

/* pathname variable values */
# ifndef NAME_MAX
#  define NAME_MAX 256 /* XXX OS dependent */
# endif
# ifndef PATH_MAX
#  define PATH_MAX 1024 /* XXX OS dependent */
# endif

/* numerical */
# ifndef CHAR_BIT
#  define CHAR_BIT 8
# endif
# ifndef CHAR_MAX
#  define CHAR_MAX SCHAR_MAX
# endif
# ifndef CHAR_MIN
#  define CHAR_MIN SCHAR_MIN
# endif
# ifndef SHRT_MAX
#  define SHRT_MAX 0x7fff
# endif
# ifndef SHRT_MIN
#  define SHRT_MIN -0x7fff
# endif
# ifndef INT_MAX
#  define INT_MAX 0x7fffffff
# endif
# ifndef INT_MIN
#  define INT_MIN -0x7fffffff
# endif
# ifndef LONG_MAX
#  ifdef _LP64 /* FIXME probably sometimes wrong */
#   define LONG_MAX 0x7fffffffffffffff
#  else
#   define LONG_MAX 0x7fffffff
#  endif
# endif
# ifndef LONG_MIN
#  ifdef _LP64 /* FIXME probably sometimes wrong */
#   define LONG_MIN 0x8000000000000000
#  else
#   define LONG_MIN -0x80000000
#  endif
# endif
# ifndef SCHAR_MAX
#  define SCHAR_MAX 0x7f
# endif
# ifndef SCHAR_MIN
#  define SCHAR_MIN -0x7f
# endif
# ifndef SSIZE_MAX
#  define SSIZE_MAX LONG_MAX
# endif
# ifndef SSIZE_MIN
#  define SSIZE_MIN LONG_MIN
# endif
# ifndef UCHAR_MAX
#  define UCHAR_MAX 0xff
# endif
# ifndef USHRT_MAX
#  define USHRT_MAX 0xffff
# endif
# ifndef UINT_MAX
#  define UINT_MAX 0xffffffff
# endif
# ifndef ULONG_MAX
#  ifdef _LP64 /* FIXME probably sometimes wrong */
#   define ULONG_MAX 0xffffffffffffffff
#  else
#   define ULONG_MAX 0xffffffff
#  endif
# endif

# ifndef DBL_MAX
#  define DBL_MAX 1.7976931348623157E+308
# endif
# ifndef FLT_MAX
#  define FLT_MAX 3.40282347E+38
# endif

#endif /* !LIBC_LIMITS_H */
