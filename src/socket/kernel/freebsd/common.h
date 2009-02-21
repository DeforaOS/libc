/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBSOCKET_KERNEL_FREEBSD_COMMON_H
# define LIBSOCKET_KERNEL_FREEBSD_COMMON_H


# define SYS_recvfrom		29
# define SYS_accept		30
# define SYS_socket		97
# define SYS_bind		104
# define SYS_listen		106
# define SYS_sendto		133

#endif /* !LIBSOCKET_KERNEL_FREEBSD_COMMON_H */
