/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_SYS_TIME_H
# define LIBC_SYS_TIME_H

# include <sys/select.h>
# include "compat/sys/time.h"


/* types */
# ifndef itimerval
#  define itimerval itimerval
struct itimerval
{
	struct timeval it_interval;
	struct timeval it_value;
};
# endif


/* functions */
int getitimer(int which, struct itimerval * value);
int gettimeofday(struct timeval * tv, void * null);
int setitimer(int which, const struct itimerval * value,
		struct itimerval * ovalue);
int utimes(char const * path, const struct timeval times[2]);

#endif /* !LIBC_SYS_TIME_H */
