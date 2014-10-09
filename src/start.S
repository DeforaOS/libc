/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
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



.text


/* _start */
.global _start


/* FreeBSD */
#if defined(__FreeBSD__)
# if defined(__amd64__)
#  include "kernel/freebsd/amd64/start.S"
# elif defined(__i386__)
#  include "kernel/freebsd/i386/start.S"
# else /* !__amd64__ && !__i386__ */
#  warning Unsupported FreeBSD architecture
# endif

/* Linux */
#elif defined(__linux__)
# if defined(__amd64__)
#  include "kernel/linux/amd64/start.S"
# elif defined(__arm__)
#  include "kernel/linux/arm/start.S"
# elif defined(__i386__)
#  include "kernel/linux/i386/start.S"
# elif defined(__sparc__)
#  include "kernel/linux/sparc/start.S"
# else /* !__arm__ && !__i386__ && !__sparc__ */
#  warning Unsupported Linux architecture
# endif

/* NetBSD */
#elif defined(__NetBSD__)
# if defined(__amd64__)
#  include "kernel/netbsd/amd64/start.S"
# elif defined(__arm__)
#  include "kernel/netbsd/arm/start.S"
# elif defined(__i386__)
#  include "kernel/netbsd/i386/start.S"
# elif defined(__sparc64__)
#  include "kernel/netbsd/sparc64/start.S"
# elif defined(__sparc__)
#  include "kernel/netbsd/sparc/start.S"
# else /* !__amd64__ && !__arm__ && !__i386__ && !__sparc__ && !__sparc64__ */
#  warning Unsupported NetBSD architecture
# endif
# include "kernel/netbsd/start.S"

/* OpenBSD */
#elif defined(__OpenBSD__)
# if defined(__arm__)
#  include "kernel/openbsd/arm/start.S"
# elif defined(__i386__)
#  include "kernel/openbsd/i386/start.S"
# else /* !__arm__ && !__i386__ */
#  warning Unsupported OpenBSD architecture
# endif

/* Solaris */
#elif defined(__sun__)
# if defined(__sparc__)
#  include "kernel/solaris/sparc/start.S"
# else
#  warning Unsupported Solaris architecture
# endif

/* Whitix */
#elif defined(__Whitix__)
# if defined(__i386__)
#  include "kernel/whitix/i386/start.S"
# else
#  warning Unsupported Whitix architecture
# endif

/* Unknown */
#else
# warning Unsupported kernel and architecture
#endif
