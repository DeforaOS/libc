/* $Id$ */
/* Copyright (c) 2008-2014 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBSOCKET_SYSCALLS_H
# define LIBSOCKET_SYSCALLS_H

# if defined(__FreeBSD__)
#  if defined(__amd64__) || defined(__i386__)
#   include "kernel/freebsd/common.h"
#  else
#   warning Unsupported FreeBSD architecture
#  endif
# elif defined(__linux__)
#  if defined(__amd64__) || defined(__arm__) || defined(__i386__)
#   include "kernel/linux/common.h"
#  else
#   warning Unsupported Linux architecture
#  endif
# elif defined(__NetBSD__)
#  if defined(__amd64__) || defined(__arm__) || defined(__i386__) \
	|| defined(__sparc__)
#   include "kernel/netbsd/common.h"
#  else
#   warning Unsupported NetBSD architecture
#  endif
# else
#  warning Unsupported platform
# endif

#endif /* !LIBSOCKET_SYSCALLS_H */
