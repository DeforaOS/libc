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



#ifndef LIBC_POLL_H
# define LIBC_POLL_H

# include "compat/poll.h"


/* types */
# ifndef pollfd
#  define pollfd pollfd
struct pollfd
{
	int fd;
	short int events;
	short int revents;
};
# endif
# ifndef nfds_t
#  define nfds_t nfds_t
typedef unsigned int nfds_t;
# endif


/* functions */
int poll(struct pollfd * fds, nfds_t nfds, int timeout);

#endif /* !LIBC_POLL_H */
