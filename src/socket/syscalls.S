/* $Id$ */
/* Copyright (c) 2008 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* libc is not free software; you can redistribute it and/or modify it under
 * the terms of the Creative Commons Attribution-NonCommercial-ShareAlike 3.0
 * Unported as published by the Creative Commons organization.
 *
 * libc is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the Creative Commons Attribution-NonCommercial-
 * ShareAlike 3.0 Unported license for more details.
 *
 * You should have received a copy of the Creative Commons Attribution-
 * NonCommercial-ShareAlike 3.0 along with libc; if not, browse to
 * http://creativecommons.org/licenses/by-nc-sa/3.0/ */



.text


/* common */
#include "../common.h"


/* Linux */
#if defined(__linux__)
# if defined(__arm__)
#  include "kernel/linux/arm/syscalls.S"
# elif defined(__i386__)
#  include "kernel/linux/i386/syscalls.S"
# else
#  warning Unsupported Linux architecture
# endif

/* NetBSD */
#elif defined(__NetBSD__)
# include "kernel/netbsd/common.h"
# if defined(__amd64__)
#  include "kernel/netbsd/amd64/syscalls.S"
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
#ifdef SYS_socket
SYSCALL(socket)
#endif
