/* $Id$ */
/* Copyright (c) 2008-2013 Pierre Pronchery <khorben@defora.org> */
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



#include "limits.h"
#include "errno.h"
#include "locale.h"


/* functions */
/* localeconv */
struct lconv * localeconv(void)
{
	static struct lconv ret;
	static int set = 0;

	if(set != 0)
		return &ret;
	set = 1;
	ret.decimal_point = ".";
	ret.thousands_sep = "";
	ret.grouping = "";
	ret.int_curr_symbol = "";
	ret.currency_symbol = "";
	ret.mon_decimal_point = "";
	ret.mon_thousands_sep = "";
	ret.mon_grouping = "";
	ret.positive_sign = "";
	ret.negative_sign = "";
	ret.int_frac_digits = CHAR_MAX;
	ret.frac_digits = CHAR_MAX;
	ret.p_cs_precedes = CHAR_MAX;
	ret.p_sep_by_space = CHAR_MAX;
	ret.n_cs_precedes = CHAR_MAX;
	ret.n_sep_by_space = CHAR_MAX;
	ret.p_sign_posn = CHAR_MAX;
	ret.n_sign_posn = CHAR_MAX;
	ret.int_p_cs_precedes = CHAR_MAX;
	ret.int_n_cs_precedes = CHAR_MAX;
	ret.int_p_sep_by_space = CHAR_MAX;
	ret.int_n_sep_by_space = CHAR_MAX;
	ret.int_p_sign_posn = CHAR_MAX;
	ret.int_n_sign_posn = CHAR_MAX;
	return &ret;
}


/* setlocale */
char * setlocale(int category, const char * locale)
{
	/* FIXME implement */
	errno = ENOSYS;
	return NULL;
}
