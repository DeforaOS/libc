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



#ifndef LIBC_LANGINFO_H
# define LIBC_LANGINFO_H

# include <nl_types.h>


/* types */
enum
{
	CODESET = 0,
	D_T_FMT, D_FMT, T_FMT, T_FMT_AMPM, AM_STR, PM_STR,
	DAY_1, DAY_2, DAY_3, DAY_4, DAY_5, DAY_6, DAY_7,
	ABDAY_1, ABDAY_2, ABDAY_3, ABDAY_4, ABDAY_5, ABDAY_6, ABDAY_7,
	MON_1, MON_2, MON_3, MON_4, MON_5, MON_6,
	MON_7, MON_8, MON_9, MON_10, MON_11, MON_12,
	ABMON_1, ABMON_2, ABMON_3, ABMON_4, ABMON_5, ABMON_6,
	ABMON_7, ABMON_8, ABMON_9, ABMON_10, ABMON_11, ABMON_12,
	ERA, ERA_D_FMT, ERA_D_T_FMT,
	ALT_DIGITS,
	RADIXCHAR,
	THOUSEP,
	YESEXPR, NOEXPR,
	CRNCYSTR
};


/* constants */
# define CODESET	CODESET
# define D_T_FMT	D_T_FMT
# define D_FMT		D_FMT
# define T_FMT		T_FMT
# define T_FMT_AMPM	T_FMT_AMPM
# define AM_STR		AM_STR
# define PM_STR		PM_STR
# define DAY_1		DAY_1
# define DAY_2		DAY_2
# define DAY_3		DAY_3
# define DAY_4		DAY_4
# define DAY_5		DAY_5
# define DAY_6		DAY_6
# define DAY_7		DAY_7
# define ABDAY_1	ABDAY_1
# define ABDAY_2	ABDAY_2
# define ABDAY_3	ABDAY_3
# define ABDAY_4	ABDAY_4
# define ABDAY_5	ABDAY_5
# define ABDAY_6	ABDAY_6
# define ABDAY_7	ABDAY_7
# define MON_1		MON_1
# define MON_2		MON_2
# define MON_3		MON_3
# define MON_4		MON_4
# define MON_5		MON_5
# define MON_6		MON_6
# define MON_7		MON_7
# define MON_8		MON_8
# define MON_9		MON_9
# define MON_10		MON_10
# define MON_11		MON_11
# define MON_12		MON_12
# define ABMON_1	ABMON_1
# define ABMON_2	ABMON_2
# define ABMON_3	ABMON_3
# define ABMON_4	ABMON_4
# define ABMON_5	ABMON_5
# define ABMON_6	ABMON_6
# define ABMON_7	ABMON_7
# define ERA		ERA
# define ERA_D_FMT	ERA_D_FMT
# define ERA_D_T_FMT	ERA_D_T_FMT
# define ALT_DIGITS	ALT_DIGITS
# define RADIXCHAR	RADIXCHAR
# define THOUSEP	THOUSEP
# define YESEXPR	YESEXPR
# define NOEXPR		NOEXPR
# define CRNCYSTR	CRNCYSTR


/* functions */
char * nl_langinfo(nl_item item);

#endif /* !LIBC_LANGINFO_H */
