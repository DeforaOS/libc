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



#ifndef LIBSOCKET_KERNEL_NETBSD_SYS_UN_H
# define LIBSOCKET_KERNEL_NETBSD_SYS_UN_H


/* types */
# ifndef sa_family_t
#  define sa_family_t sa_family_t
typedef unsigned char sa_family_t;
# endif

# ifndef sockaddr_un
#  define sockaddr_un sockaddr_un
struct sockaddr_un
{
	unsigned char sun_len;
	sa_family_t sun_family;
	char sun_path[104];
};
# endif

#endif /* !LIBSOCKET_KERNEL_NETBSD_SYS_UN_H */
