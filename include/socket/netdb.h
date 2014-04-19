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



#ifndef LIBSOCKET_NETDB_H
# define LIBSOCKET_NETDB_H

# include <netinet/in.h>


/* types */
# ifndef addrinfo
#  define addrinfo addrinfo
struct addrinfo
{
	int ai_flags;
	int ai_family;
	int ai_socktype;
	int ai_protocol;
	socklen_t ai_addrlen;
	struct sockaddr * ai_addr;
	char * ai_canonname;
	struct addrinfo * ai_next;
};
# endif

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

# define EAI_AGAIN			1
# define EAI_BADFLAGS			2
# define EAI_FAIL			3
# define EAI_FAMILY			4
# define EAI_MEMORY			5
# define EAI_NONAME			6
# define EAI_OVERFLOW			7
# define EAI_SERVICE			8
# define EAI_SOCKTYPE			9
# define EAI_SYSTEM			10

# define NI_NOFQDN			0x01
# define NI_NUMERICHOST			0x02
# define NI_NAMEREQD			0x04
# define NI_NUMERICSERV			0x08
# define NI_NUMERICSCOPE		0x10
# define NI_DGRAM			0x20


/* variables */
extern int h_errno;


/* functions */
void endhostent(void);
void endservent(void);
void freeaddrinfo(struct addrinfo * ai);
const char * gai_strerror(int ecode);
int getaddrinfo(char const * nodename, char const * servname,
		struct addrinfo const * hints, struct addrinfo ** res);
struct hostent * gethostbyaddr(const void * addr, socklen_t len, int type);
struct hostent * gethostbyname(const char * name);
int getnameinfo(const struct sockaddr * sa, socklen_t salen, char * node,
		socklen_t nodelen, char * service, socklen_t servicelen,
		int flags);
struct servent * getservbyname(const char * name, const char * protocol);
struct servent * getservbyport(int port, const char * protocol);
struct servent * getservent(void);
struct hostent * gethostent(void);
char * hstrerror(int errnum);
void sethostent(int stayopen);
void setservent(int stayopen);

#endif /* !LIBSOCKET_NETDB_H */
