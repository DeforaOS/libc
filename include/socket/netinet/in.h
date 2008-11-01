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



#ifndef LIBSOCKET_NETINET_IN_H
# define LIBSOCKET_NETINET_IN_H

# include <sys/socket.h>
# include <inttypes.h>
# include "compat/netinet/in.h"


/* constants */
# define INADDR_ANY		0x00000000
# define INADDR_BROADCAST	0xffffffff

# define IPPROTO_IP		0
# define IPPROTO_ICMP		1
# define IPPROTO_TCP		6
# define IPPROTO_UDP		17

#endif /* !LIBSOCKET_NETINET_IN_H */
