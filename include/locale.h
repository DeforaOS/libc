/* $Id$ */
/* Copyright (c) 2008 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_LOCALE_H
# define LIBC_LOCALE_H


/* types */
# ifndef lconv
#  define lconv lconv
struct lconv
{
	char * currency_symbol;
	char * decimal_point;
	char frac_digits;
	char * grouping;
	char * int_curr_symbol;
	char int_frac_digits;
	char int_n_cs_precedes;
	char int_n_sep_by_space;
	char int_n_sign_posn;
	char int_p_cs_precedes;
	char int_p_sep_by_space;
	char int_p_sign_posn;
	char * mon_decimal_point;
	char * mon_grouping;
	char * mon_thousands_sep;
	char * negative_sign;
	char n_cs_precedes;
	char n_sep_by_space;
	char n_sign_posn;
	char * positive_sign;
	char p_cs_precedes;
	char p_sep_by_space;
	char p_sign_posn;
	char * thousands_sep;
};
# endif


/* constants */
# ifndef NULL
#  define NULL ((void*)0)
# endif

# define LC_ALL		0
# define LC_COLLATE	1
# define LC_CTYPE	2
# define LC_MESSAGES	3
# define LC_MONETARY	4
# define LC_NUMERIC	5
# define LC_TIME	6


/* functions */
struct lconv * localeconv(void);
char * setlocale(int category, const char * locale);

#endif /* !LIBC_LOCALE_H */
