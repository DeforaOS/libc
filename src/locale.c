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
