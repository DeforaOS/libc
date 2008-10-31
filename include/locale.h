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
