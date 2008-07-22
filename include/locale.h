/* $Id$ */
/* Copyright (c) 2008 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* libc is not free software; you can redistribute it and/or modify it under
 * the terms of the Creative Commons Attribution-NonCommercial-ShareAlike 3.0
 * Unported as published by the Creative Commons organization.
 *
 * libc is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the Creative Commons Attribution-NonCommercial-
 * ShareAlike 3.0 Unported license for more details.
 *
 * You should have received a copy of the Creative Commons Attribution-
 * NonCommercial-ShareAlike 3.0 along with libc; if not, browse to
 * http://creativecommons.org/licenses/by-nc-sa/3.0/ */



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
