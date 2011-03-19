/* $Id$ */
/* Copyright (c) 2011 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBSOCKET_KERNEL_NETBSD_NETINET_IN_H
# define LIBSOCKET_KERNEL_NETBSD_NETINET_IN_H


/* types */
# ifndef in_addr_t
#  define in_addr_t in_addr_t
typedef uint32_t in_addr_t;
# endif

# ifndef in_port_t
#  define in_port_t in_port_t
typedef uint16_t in_port_t;
#endif

# ifndef in_addr
#  define in_addr in_addr
struct in_addr
{
	in_addr_t s_addr;
};
# endif

# ifndef in6_addr
#  define in6_addr in6_addr
struct in6_addr
{
	uint8_t s6_addr[16];
};
# endif

# ifndef sockaddr_in
#  define sockaddr_in sockaddr_in
struct sockaddr_in
{
	unsigned char sin_len;
	sa_family_t sin_family;
	in_port_t sin_port;
	struct in_addr sin_addr;
	char _padding[8];
};
# endif

#endif /* !LIBSOCKET_KERNEL_NETBSD_NETINET_IN_H */
