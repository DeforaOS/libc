/* $Id$ */
/* Copyright (c) 2008 Pierre Pronchery <khorben@defora.org> */
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


/* constants */
# define HOST_NOT_FOUND			1
# define NO_DATA			2
# define NO_RECOVERY			3
# define TRY_AGAIN			4


/* variables */
extern int h_errno;


/* functions */
struct hostent * gethostbyaddr(const void * addr, socklen_t len, int type);
struct hostent * gethostbyname(const char * name);
struct servent * getservbyname(const char * name, const char * protocol);

#endif /* !LIBSOCKET_NETDB_H */
