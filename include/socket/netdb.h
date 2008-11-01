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



#ifndef LIBSOCKET_NETDB_H
# define LIBSOCKET_NETDB_H

# include <netinet/in.h>


/* types */
# ifndef hostent
#  define hostent hostent
struct hostent
{
	char * h_name;
	char ** h_aliases;
	int h_addrtype;
	int h_length;
	char ** h_addr_list;
};
# endif

# ifndef servent
#  define servent servent
struct servent
{
	char * s_name;
	char ** s_aliases;
	int s_port;
	char * s_proto;
};
# endif


/* functions */
struct hostent * gethostbyaddr(const void * addr, socklen_t len, int type);
struct hostent * gethostbyname(const char * name);
struct servent * getservbyname(const char * name, const char * protocol);

#endif /* !LIBSOCKET_NETDB_H */
