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



#include <sys/types.h>
#include <sys/ptrace.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


/* prototypes */
static int _ptrace(char const * progname);

static int _error(char const * progname, char const * message, int ret);


/* functions */
/* ptrace */
static int _ptrace(char const * progname)
{
	if(ptrace(PT_TRACE_ME, 0, NULL, 0) != 0)
		return -_error(progname, "PT_TRACE_ME", 1);
	if(ptrace(PT_ATTACH, getpid(), NULL, 0) != 0
			&& errno != EBUSY && errno != EINVAL)
		return -_error(progname, "PT_ATTACH", 1);
	return 0;
}


/* error */
static int _error(char const * progname, char const * message, int ret)
{
	fprintf(stderr, "%s: %s: %s\n", progname, message, strerror(errno));
	return ret;
}


/* main */
int main(int argc, char * argv[])
{
	int ret = 0;

	ret |= _ptrace(argv[0]);
	return (ret == 0) ? 0 : 2;
}
