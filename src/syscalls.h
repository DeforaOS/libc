/* $Id$ */
/* Copyright (c) 2004-2012 Pierre Pronchery <khorben@defora.org> */
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



#ifndef SYSCALLS_H
# define SYSCALLS_H

/* FreeBSD */
# if defined(__FreeBSD__)
#  if defined(__amd64__) || defined(__i386__)
#   include "sys/syscall.h"
#  else
#   warning Unsupported FreeBSD architecture
#  endif

/* Linux */
# elif defined(__linux__)
#  if defined(__amd64__) || defined(__arm__) || defined(__i386__)
#   include "sys/syscall.h"
#  else
#   warning Unsupported Linux architecture
#  endif

/* MacOS X */
# elif defined(__APPLE__)
#  if defined(__amd64__)
#   include "sys/syscall.h"
#   include "kernel/darwin/common.h"
#  else
#   warning Unsupported Darwin architecture
#  endif

/* NetBSD */
# elif defined(__NetBSD__)
#  if defined(__amd64__) || defined(__arm__) || defined(__i386__) \
	|| defined(__sparc__)
#   include "sys/syscall.h"
#   include "kernel/netbsd/sys/sysctl.h"
#  else
#   warning Unsupported NetBSD architecture
#  endif

/* OpenBSD */
# elif defined(__OpenBSD__)
#  if defined(__arm__) || defined(__i386__)
#   include "sys/syscall.h"
#  else
#   warning Unsupported OpenBSD architecture
#  endif

/* Solaris */
# elif defined(__sun__)
#  if defined(__sparc__)
#   include "sys/syscall.h"
#   include "kernel/solaris/common.h"
#  else
#   warning Unsupported Solaris architecture
#  endif

/* Whitix */
# elif defined(__Whitix__)
#  if defined(__i386__)
#   include "sys/syscall.h"
#   include "kernel/whitix/common.h"
#  else
#   warning Unsupported Solaris architecture
#  endif

/* Unknown */
#else
# warning Unsupported platform
#endif

#endif /* !SYSCALLS_H */
