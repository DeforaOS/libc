/* $Id$ */
/* Copyright (c) 2012 Pierre Pronchery <khorben@defora.org> */
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



#include "stdio.h"
#include "string.h"
#include "errno.h"
#include "regex.h"


/* functions */
/* regcomp */
int regcomp(regex_t * regex, const char * pattern, int flags)
{
	/* FIXME really implement */
	return REG_ENOSYS;
}


/* regerror */
size_t regerror(int error, const regex_t * regex, char * buf, size_t buf_cnt)
{
	int res;

	if((res = snprintf(buf, buf_cnt, "%s", strerror(ENOSYS))) <= 0)
		return 0;
	return res;
}


/* regexec */
int regexec(const regex_t * regex, const char * string, size_t match_cnt,
		regmatch_t match[], int flags)
{
	/* FIXME really implement */
	return REG_ENOSYS;
}


/* regfree */
void regfree(regex_t * regex)
{
}
