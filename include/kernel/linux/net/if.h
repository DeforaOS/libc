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



#ifndef LIBC_KERNEL_LINUX_NET_IF_H
# define LIBC_KERNEL_LINUX_NET_IF_H


/* types */
# ifndef sa_family_t
#  define sa_family_t sa_family_t
typedef unsigned short int sa_family_t;
# endif

# ifndef sockaddr
#  define sockaddr sockaddr
struct sockaddr
{
	sa_family_t sa_family;
	char sa_data[14];
};
# endif

# ifndef ifreq
#  define ifreq ifreq
#  define IFNAMSIZ 16
struct ifreq
{
	char ifr_name[IFNAMSIZ];
	union
	{
		struct sockaddr ifru_addr;
		short ifru_flags;
	} ifr_ifru;
};
#  define ifr_addr	ifr_ifru.ifru_addr
#  define ifr_flags	ifr_ifru.ifru_flags
# endif


/* constants */
# define SIOCGIFADDR	0x8915

#endif /* !LIBC_KERNEL_LINUX_NET_IF_H */
