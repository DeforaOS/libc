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



#ifndef LIBC_KERNEL_NETBSD_POLL_H
# define LIBC_KERNEL_NETBSD_POLL_H


/* constants */
# define POLLIN		0x001
# define POLLPRI	0x002
# define POLLOUT	0x004
# define POLLERR	0x008
# define POLLHUP	0x010
# define POLLNVAL	0x020
# define POLLRDNORM	0x040
# define POLLRDBAND	0x080
# define POLLWRBAND	0x100
# define POLLWRNORM	POLLOUT

#endif /* !LIBC_KERNEL_NETBSD_POLL_H */
