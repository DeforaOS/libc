/* $Id$ */
/* Copyright (c) 2010 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBSOCKET_KERNEL_NETBSD_COMMON_H
# define LIBSOCKET_KERNEL_NETBSD_COMMON_H


# define SYS_recvfrom		29
# define SYS_accept		30
# define SYS_getsockname	32
# define SYS_connect		98
# define SYS_bind		104
# define SYS_setsockopt		105
# define SYS_listen		106
# define SYS_getsockopt		118
# define SYS_sendto		133
# define SYS_shutdown		134
# define SYS_socketpair		135
# define SYS_socket		394

#endif /* !LIBSOCKET_KERNEL_NETBSD_COMMON_H */
