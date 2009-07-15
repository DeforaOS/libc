/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
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
