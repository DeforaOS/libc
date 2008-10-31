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



#ifndef LIBC_SYS_SELECT_H
# define LIBC_SYS_SELECT_H

# include "compat/sys/select.h"


/* types */
# ifndef fd_set
#  define fd_set fd_set
typedef struct _fd_set fd_set;
# endif
# ifndef itimerval
#  define itimerval itimerval
struct itimerval
{
	struct timeval it_interval;
	struct timeval it_value;
};
# endif


/* functions */
int select(int fdcnt, fd_set * rfds, fd_set * wfds, fd_set * efds,
		struct timeval * timeout);

#endif /* !LIBC_SYS_SELECT_H */
