/* $Id$ */
/* Copyright (c) 2008-2014 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */



#ifndef LIBSOCKET_NETDB_H
# define LIBSOCKET_NETDB_H

# include <inttypes.h>
# include <netinet/in.h>
# include <netinet6/in6.h>


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

# ifndef netent
#  define netent netent
struct netent
{
	char * n_name;
	char ** n_aliases;
	int n_addrtype;
	uint32_t n_net;
};
# endif

# ifndef protoent
#  define protoent protoent
struct protoent
{
	char * p_name;
	char ** p_aliases;
	int p_proto;
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

# define AI_PASSIVE			0x01

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
void endnetent(void);
void endprotoent(void);
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
struct netent * getnetbyaddr(uint32_t net, int type);
struct netent * getnetbyname(const char * name);
struct netent * getnetent(void);
struct protoent * getprotobyname(const char * name);
struct protoent * getprotobynumber(int proto);
struct protoent * getprotoent(void);
struct servent * getservbyname(const char * name, const char * protocol);
struct servent * getservbyport(int port, const char * protocol);
struct servent * getservent(void);
struct hostent * gethostent(void);
char * hstrerror(int errnum);
void sethostent(int stayopen);
void setnetent(int stayopen);
void setprotoent(int stayopen);
void setservent(int stayopen);

#endif /* !LIBSOCKET_NETDB_H */
