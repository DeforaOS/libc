/* $Id$ */
/* Copyright (c) 2010 Pierre Pronchery <khorben@defora.org> */
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
#  define SYS_getpeername	52
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
#  define SYS_getpeername	205
# endif

#endif /* !KERNEL_SOCKET_LINUX_COMMON_H */
