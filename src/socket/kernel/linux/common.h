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



#ifndef SOCKET_KERNEL_LINUX_COMMON_H
# define SOCKET_KERNEL_LINUX_COMMON_H


# ifdef __amd64__
#  define SYS_socket		41
#  define SYS_connect		42
#  define SYS_accept		43
#  define SYS_sendto		44
#  define SYS_recvfrom		45
#  define SYS_send		46 /* FIXME is this correct? */
#  define SYS_sendmsg		46
#  define SYS_recv		47 /* FIXME is this correct? */
#  define SYS_recvmsg		47
#  define SYS_shutdown		48
#  define SYS_bind		49
#  define SYS_listen		50
#  define SYS_getsockname	51
#  define SYS_socketpair	53
#  define SYS_setsockopt	54
#  define SYS_getsockopt	55
# else
#  define SYS_socket		1
#  define SYS_bind		2
#  define SYS_connect		3
#  define SYS_listen		4
#  define SYS_accept		5
#  define SYS_getsockname	6
#  define SYS_socketpair	8
#  define SYS_recv		9
#  define SYS_send		10
#  define SYS_sendto		11
#  define SYS_recvfrom		12
#  define SYS_shutdown		13
#  define SYS_setsockopt	14
#  define SYS_getsockopt	15
#  define SYS_sendmsg		16
#  define SYS_recvmsg		17
#  define SYS_socketcall	102
# endif

#endif /* !KERNEL_SOCKET_LINUX_COMMON_H */
