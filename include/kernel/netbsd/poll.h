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



#ifndef LIBC_KERNEL_NETBSD_POLL_H
# define LIBC_KERNEL_NETBSD_POLL_H


/* constants */
# define POLLIN		0x001
# define POLLPRI	0x002
# define POLLOUT	0x004
# define POLLERR	0x008
# define POLLHUP	0x010
# define POLLNVAL	0x020
# define POLLRDNORM	0x040
# define POLLRDBAND	0x080
# define POLLWRBAND	0x100
# define POLLWRNORM	POLLOUT

#endif /* !LIBC_KERNEL_NETBSD_POLL_H */
