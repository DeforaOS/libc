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



#ifndef LIBSOCKET_KERNEL_FREEBSD_SYS_SOCKET_H
# define LIBSOCKET_KERNEL_FREEBSD_SYS_SOCKET_H


/* types */
# ifndef sa_family_t
#  define sa_family_t sa_family_t
typedef unsigned char sa_family_t;
# endif

# ifndef sockaddr
#  define sockaddr sockaddr
struct sockaddr
{
	unsigned char sa_len;
	sa_family_t sa_family;
	char sa_data[14];
};
# endif


/* constants */
# define MSG_NOSIGNAL		0x20000

# define SOL_SOCKET		0xffff

# define SHUT_RD		0
# define SHUT_WR		1
# define SHUT_RDWR		2

#endif /* !LIBSOCKET_KERNEL_FREEBSD_SYS_SOCKET_H */
