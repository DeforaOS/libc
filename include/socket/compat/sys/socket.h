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



#ifndef LIBSOCKET_COMPAT_SYS_SOCKET_H
# define LIBSOCKET_COMPAT_SYS_SOCKET_H


# if defined(__FreeBSD__)
#  include "kernel/freebsd/sys/socket.h"
# elif defined(__linux__)
#  include "kernel/linux/sys/socket.h"
# elif defined(__NetBSD__)
#  include "kernel/netbsd/sys/socket.h"
# else
#  warning Unsupported platform
# endif

#endif /* !LIBSOCKET_COMPAT_SYS_SOCKET_H */
