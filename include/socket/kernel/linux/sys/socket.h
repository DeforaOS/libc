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



#ifndef LIBSOCKET_KERNEL_LINUX_SYS_SOCKET_H
# define LIBSOCKET_KERNEL_LINUX_SYS_SOCKET_H


/* types */
# ifndef sa_family_t
#  define sa_family_t sa_family_t
typedef unsigned short int sa_family_t;
# endif

# ifndef sockaddr
#  define sockaddr sockaddr
struct sockaddr
{
	sa_family_t sa_family;
	char sa_data[14];
};
# endif


/* constants */
# define MSG_NOSIGNAL		0x4000

# define SOL_SOCKET		1

# define SHUT_RD		0
# define SHUT_WR		1
# define SHUT_RDWR		2

#endif /* !LIBSOCKET_KERNEL_LINUX_SYS_SOCKET_H */
