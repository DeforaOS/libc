/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */



#ifndef LIBC_LIMITS_H
# define LIBC_LIMITS_H

# include "compat/limits.h"


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
