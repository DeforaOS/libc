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



#ifndef LIBSOCKET_KERNEL_LINUX_NETINET_IN_H
# define LIBSOCKET_KERNEL_LINUX_NETINET_IN_H


/* types */
# ifndef in_addr_t
#  define in_addr_t in_addr_t
typedef uint32_t in_addr_t;
# endif

# ifndef in_port_t
#  define in_port_t in_port_t
typedef uint16_t in_port_t;
#endif

# ifndef in_addr
#  define in_addr in_addr
struct in_addr
{
	in_addr_t s_addr;
};
# endif

# ifndef sockaddr_in
#  define sockaddr_in sockaddr_in
struct sockaddr_in
{
	sa_family_t sin_family;
	in_port_t sin_port;
	struct in_addr sin_addr;
	char _padding[8];		/* FIXME not checked */
};
# endif

#endif /* !LIBSOCKET_KERNEL_LINUX_NETINET_IN_H */
