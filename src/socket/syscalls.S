/* $Id$ */
/* Copyright (c) 2008-2017 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */



#include "syscalls.h"


.text


/* FreeBSD */
#if defined(__FreeBSD__)
# if defined(__amd64__)
#  include "kernel/freebsd/amd64/syscalls.S"
# elif defined(__i386__)
#  include "kernel/freebsd/i386/syscalls.S"
# else
#  warning Unsupported FreeBSD architecture
# endif

/* Linux */
#elif defined(__linux__)
# if defined(__amd64__)
#  include "kernel/linux/amd64/syscalls.S"
# elif defined(__arm__)
#  include "kernel/linux/arm/syscalls.S"
# elif defined(__i386__)
#  include "kernel/linux/i386/syscalls.S"
# else
#  warning Unsupported Linux architecture
# endif

/* macOS */
#elif defined(__APPLE__)
# if defined(__amd64__)
#  include "kernel/darwin/amd64/syscalls.S"
# else
#  warning Unsupported macOS architecture
# endif

/* NetBSD */
#elif defined(__NetBSD__)
# if defined(__amd64__)
#  include "kernel/netbsd/amd64/syscalls.S"
# elif defined(__arm__)
#  include "kernel/netbsd/arm/syscalls.S"
# elif defined(__i386__)
#  include "kernel/netbsd/i386/syscalls.S"
# elif defined(__sparc__)
#  include "kernel/netbsd/sparc/syscalls.S"
# else
#  warning Unsupported NetBSD architecture
# endif

/* OpenBSD */
#elif defined(__OpenBSD__)
# if defined(__arm__)
#  include "kernel/openbsd/arm/syscalls.S"
# elif defined(__i386__)
#  include "kernel/openbsd/i386/syscalls.S"
# else /* !__arm__ && !__i386__ */
#  warning Unsupported OpenBSD architecture
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
#ifdef SYS_getpeername
SYSCALL(getpeername)
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
#ifdef SYS_recvmsg
SYSCALL(recvmsg)
#endif
#ifdef SYS_send
SYSCALL(send)
#endif
#ifdef SYS_sendmsg
SYSCALL(sendmsg)
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
#ifdef SYS_socketpair
SYSCALL(socketpair)
#endif
