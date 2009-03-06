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



#include "syscalls.h"


.text


/* FreeBSD */
#if defined(__FreeBSD__)
# if defined(__amd64__)
#  include "kernel/freebsd/amd64/syscalls.S"
# else
#  warning Unsupported FreeBSD architecture
# endif

/* Linux */
#elif defined(__linux__)
# if defined(__arm__)
#  include "kernel/linux/arm/syscalls.S"
# elif defined(__i386__)
#  include "kernel/linux/i386/syscalls.S"
# else
#  warning Unsupported Linux architecture
# endif

/* NetBSD */
#elif defined(__NetBSD__)
# if defined(__amd64__)
#  include "kernel/netbsd/amd64/syscalls.S"
# elif defined(__i386__)
#  include "kernel/netbsd/i386/syscalls.S"
# elif defined(__sparc__)
#  include "kernel/netbsd/sparc/syscalls.S"
# else
#  warning Unsupported NetBSD architecture
# endif

/* Unknown */
#else
# warning Unsupported platform
#endif
#ifndef SYSCALL
# define SYSCALL(name)
#endif


/* sys/socket.h */
#ifdef SYS_accept
SYSCALL(accept)
#endif
#ifdef SYS_bind
SYSCALL(bind)
#endif
#ifdef SYS_connect
SYSCALL(connect)
#endif
#ifdef SYS_getsockname
SYSCALL(getsockname)
#endif
#ifdef SYS_getsockopt
SYSCALL(getsockopt)
#endif
#ifdef SYS_listen
SYSCALL(listen)
#endif
#ifdef SYS_recv
SYSCALL(recv)
#endif
#ifdef SYS_recvfrom
SYSCALL(recvfrom)
#endif
#ifdef SYS_send
SYSCALL(send)
#endif
#ifdef SYS_sendto
SYSCALL(sendto)
#endif
#ifdef SYS_setsockopt
SYSCALL(setsockopt)
#endif
#ifdef SYS_shutdown
SYSCALL(shutdown)
#endif
#ifdef SYS_socket
SYSCALL(socket)
#endif
