/* $Id$ */
/* Copyright (c) 2008-2016 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBSOCKET_SYSCALLS_H
# define LIBSOCKET_SYSCALLS_H

/* FreeBSD */
# if defined(__FreeBSD__)
#  if defined(__amd64__) || defined(__i386__)
#   include "kernel/freebsd/common.h"
#  else
#   warning Unsupported FreeBSD architecture
#  endif

/* Linux */
# elif defined(__linux__)
#  if defined(__amd64__) || defined(__arm__) || defined(__i386__)
#   include "kernel/linux/common.h"
#  else
#   warning Unsupported Linux architecture
#  endif

/* NetBSD */
# elif defined(__NetBSD__)
#  if defined(__amd64__) || defined(__arm__) || defined(__i386__) \
	|| defined(__sparc__)
#   include "kernel/netbsd/common.h"
#  else
#   warning Unsupported NetBSD architecture
#  endif

/* OpenBSD */
# elif defined(__OpenBSD__)
#  if defined(__arm__) || defined(__i386__)
#   include "kernel/openbsd/common.h"
#  else
#   warning Unsupported OpenBSD architecture
#  endif

/* Unknown */
# else
#  warning Unsupported platform
# endif

#endif /* !LIBSOCKET_SYSCALLS_H */
