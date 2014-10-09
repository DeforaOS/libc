/* $Id$ */
/* Copyright (c) 2013 Pierre Pronchery <khorben@defora.org> */
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



#include <stdio.h>
#include <langinfo.h>


/* langinfo */
static int _langinfo(char const * progname, nl_item item)
{
	printf("%s: nl_langinfo(%lu) returns \"%s\"\n", progname, item,
			nl_langinfo(item));
	return 0;
}


/* main */
int main(int argc, char * argv[])
{
	int res = 0;

	res += _langinfo(argv[0], CODESET);
	res += _langinfo(argv[0], D_T_FMT);
	res += _langinfo(argv[0], D_FMT);
	res += _langinfo(argv[0], T_FMT);
	res += _langinfo(argv[0], T_FMT_AMPM);
	res += _langinfo(argv[0], AM_STR);
	res += _langinfo(argv[0], PM_STR);
	res += _langinfo(argv[0], DAY_1);
	res += _langinfo(argv[0], DAY_2);
	res += _langinfo(argv[0], DAY_3);
	res += _langinfo(argv[0], DAY_4);
	res += _langinfo(argv[0], DAY_5);
	res += _langinfo(argv[0], DAY_6);
	res += _langinfo(argv[0], DAY_7);
	res += _langinfo(argv[0], ABDAY_1);
	res += _langinfo(argv[0], ABDAY_2);
	res += _langinfo(argv[0], ABDAY_3);
	res += _langinfo(argv[0], ABDAY_4);
	res += _langinfo(argv[0], ABDAY_5);
	res += _langinfo(argv[0], ABDAY_6);
	res += _langinfo(argv[0], ABDAY_7);
	res += _langinfo(argv[0], MON_1);
	res += _langinfo(argv[0], MON_2);
	res += _langinfo(argv[0], MON_3);
	res += _langinfo(argv[0], MON_4);
	res += _langinfo(argv[0], MON_5);
	res += _langinfo(argv[0], MON_6);
	res += _langinfo(argv[0], MON_7);
	res += _langinfo(argv[0], MON_8);
	res += _langinfo(argv[0], MON_9);
	res += _langinfo(argv[0], MON_10);
	res += _langinfo(argv[0], MON_11);
	res += _langinfo(argv[0], MON_12);
	res += _langinfo(argv[0], ABMON_1);
	res += _langinfo(argv[0], ABMON_2);
	res += _langinfo(argv[0], ABMON_3);
	res += _langinfo(argv[0], ABMON_4);
	res += _langinfo(argv[0], ABMON_5);
	res += _langinfo(argv[0], ABMON_6);
	res += _langinfo(argv[0], ABMON_7);
	res += _langinfo(argv[0], ABMON_8);
	res += _langinfo(argv[0], ABMON_9);
	res += _langinfo(argv[0], ABMON_10);
	res += _langinfo(argv[0], ABMON_11);
	res += _langinfo(argv[0], ABMON_12);
	res += _langinfo(argv[0], ERA);
	res += _langinfo(argv[0], ERA_D_FMT);
	res += _langinfo(argv[0], ERA_D_T_FMT);
	res += _langinfo(argv[0], ERA_T_FMT);
	res += _langinfo(argv[0], ALT_DIGITS);
	res += _langinfo(argv[0], RADIXCHAR);
	res += _langinfo(argv[0], THOUSEP);
	res += _langinfo(argv[0], YESEXPR);
	res += _langinfo(argv[0], NOEXPR);
	res += _langinfo(argv[0], CRNCYSTR);
	return (res == 0) ? 0 : 2;
}
