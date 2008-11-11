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



#ifndef LIBSOCKET_NETINET_IN_H
# define LIBSOCKET_NETINET_IN_H

# include <sys/socket.h>
# include <inttypes.h>
# include "compat/netinet/in.h"


/* constants */
# define INADDR_ANY		0x00000000
# define INADDR_BROADCAST	0xffffffff
# define INADDR_LOOPBACK	0x7f000001

# define IPPROTO_IP		0
# define IPPROTO_ICMP		1
# define IPPROTO_TCP		6
# define IPPROTO_UDP		17

#endif /* !LIBSOCKET_NETINET_IN_H */
