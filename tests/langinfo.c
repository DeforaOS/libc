/* $Id$ */
/* Copyright (c) 2013 Pierre Pronchery <khorben@defora.org> */
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



#include <stdio.h>
#include <langinfo.h>


/* langinfo */
static int _langinfo(char const * progname, nl_item item)
{
	printf("%s: nl_langinfo(%lu) returns %s\n", progname,
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
