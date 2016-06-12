/* $Id$ */
/* Copyright (c) 2008-2013 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_WCHAR_H
# define LIBC_WCHAR_H


/* types */
/* FIXME check if wchar_t is correct */
# ifndef FILE
#  define FILE FILE
typedef struct _FILE FILE;
# endif
# ifndef mbstate_t
#  define mbstate_t mbstate_t
typedef struct _mbstate_t
{
	char data[128];
} mbstate_t;
# endif
# ifndef size_t
#  define size_t size_t
typedef unsigned long size_t;
# endif
# ifndef wchar_t
#  define wchar_t wchar_t
#  ifdef __WCHAR_TYPE__
typedef __WCHAR_TYPE__ wchar_t;
#  else
typedef char wchar_t;
#  endif
# endif
# ifndef wint_t
#  define wint_t wint_t
#  ifdef __WINT_TYPE__
typedef __WINT_TYPE__ wint_t;
#  else
typedef int wint_t;
#  endif
# endif


/* constants */
# ifndef NULL
#  define NULL ((void *)0)
# endif
# ifndef WEOF
#  define WEOF (-1)
# endif


/* functions */
size_t mbrtowc(wchar_t * pwc, const char * s, size_t n, mbstate_t * ps);
size_t mbstowcs(wchar_t * pwcs, const char * s, size_t n);
int mbtowc(wchar_t * pwc, const char * s, size_t n);

#endif /* !LIBC_WCHAR_H */
