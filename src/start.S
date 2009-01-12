/* $Id$ */
/* Copyright (c) 2007 Pierre Pronchery <khorben@defora.org> */
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


/* _start */
.global _start


/* Linux */
#if defined(__linux__)
# if defined(__arm__)
#  include "kernel/linux/arm/start.S"
# elif defined(__i386__)
#  include "kernel/linux/i386/start.S"
# elif defined(__sparc__)
#  include "kernel/linux/sparc/start.S"
# else /* !__i386__ && !__sparc__ */
#  warning Unsupported Linux architecture
# endif

/* FreeBSD */
#elif defined(__FreeBSD__)
# if defined(__i386__)
#  include "kernel/freebsd/i386/start.S"
# else /* !__i386__ */
#  warning Unsupported FreeBSD architecture
# endif

/* NetBSD */
#elif defined(__NetBSD__)
# if defined(__amd64__)
#  include "kernel/netbsd/amd64/start.S"
# elif defined(__i386__)
#  include "kernel/netbsd/i386/start.S"
# elif defined(__sparc64__)
#  include "kernel/netbsd/sparc64/start.S"
# elif defined(__sparc__)
#  include "kernel/netbsd/sparc/start.S"
# else /* !__amd64__ && !__i386__ && !__sparc__ && !__sparc64__ */
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
