/* $Id$ */
/* Copyright (c) 2005-2016 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_INTTYPES_H
# define LIBC_INTTYPES_H

# include <stdint.h>


/* types */
# ifndef imaxdiv_t
#  define imaxdiv_t imaxdiv_t
typedef struct _imaxdiv_t
{
	intmax_t quot;
	intmax_t rem;
} imaxdiv_t;
# endif
# ifndef wchar_t
#  define wchar_t wchar_t
typedef char wchar_t;
# endif


/* constants */
#ifdef __INTPTR_FMTd__
# define PRId8		__INT8_FMTd__
# define PRId16		__INT16_FMTd__
# define PRId32		__INT32_FMTd__
# define PRId64		__INT64_FMTd__
# define PRIdMAX	__INTMAX_FMTd__
# define PRIdPTR	__INTPTR_FMTd__
#elif _LP64
# define PRId8		"d"
# define PRId16		"d"
# define PRId32		"d"
# define PRId64		"ld"
# define PRIdMAX	"ld"
# define PRIdPTR	"ld"
#else
# define PRId8		"d"
# define PRId16		"d"
# define PRId32		"d"
# define PRId64		"lld"
# define PRIdMAX	"lld"
# define PRIdPTR	"d"
#endif


/* functions */
intmax_t imaxabs(intmax_t);
imaxdiv_t imaxdiv(intmax_t, intmax_t);
intmax_t strtoimax(const char *, char **, int);
uintmax_t strtoumax(const char *, char **, int);
intmax_t wcstoimax(const wchar_t *, wchar_t **, int);
uintmax_t wcstoumax(const wchar_t *, wchar_t **, int);

#endif /* !LIBC_INTTYPES_H */
