/* $Id$ */
/* Copyright (c) 2013-2016 Pierre Pronchery <khorben@defora.org> */
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



#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>


/* prototypes */
static int _netdb(char const * progname);

static int _gai_strerror(char const * message, int value);
static int _getaddrinfo(char const * progname);
static int _gethostbyaddr(char const * addr, size_t length, int type);
static int _gethostent(void);
static int _getnameinfo(char const * progname);
static int _getnetent(void);
static int _getprotoent(void);
static int _getservbyname(char const * name, char const * protocol);
static int _getservbyport(int port, char const * protocol);
static int _getservent(void);
static int _hstrerror(char const * message, int value);


/* functions */
/* netdb */
static int _netdb(char const * progname)
{
	int ret = 0;

	/* gethostbyaddr */
	ret |= _gethostbyaddr("\x7f\x00\x00\x01", 4, AF_INET);
	/* gethostent */
	ret |= _gethostent();
	/* getnameinfo */
	ret |= _getnameinfo(progname);
	/* getnetent */
	ret |= _getnetent();
	/* getprotoent */
	ret |= _getprotoent();
	/* getservent */
	ret |= _getservbyname("ssh", "tcp");
	ret |= _getservbyport(22, "tcp");
	ret |= _getservent();
	/* hstrerror */
	ret |= _hstrerror("HOST_NOT_FOUND", HOST_NOT_FOUND);
	ret |= _hstrerror("TRY_AGAIN", TRY_AGAIN);
	ret |= _hstrerror("NO_RECOVERY", NO_RECOVERY);
	ret |= _hstrerror("NO_DATA", NO_DATA);
	/* gai_strerror */
	ret |= _gai_strerror("EAI_AGAIN", EAI_AGAIN);
	ret |= _gai_strerror("EAI_BADFLAGS", EAI_BADFLAGS);
	ret |= _gai_strerror("EAI_FAIL", EAI_FAIL);
	ret |= _gai_strerror("EAI_FAMILY", EAI_FAMILY);
	ret |= _gai_strerror("EAI_MEMORY", EAI_MEMORY);
	ret |= _gai_strerror("EAI_NONAME", EAI_NONAME);
	ret |= _gai_strerror("EAI_OVERFLOW", EAI_OVERFLOW);
	ret |= _gai_strerror("EAI_SERVICE", EAI_SERVICE);
	ret |= _gai_strerror("EAI_SOCKTYPE", EAI_SOCKTYPE);
	ret |= _gai_strerror("EAI_SYSTEM", EAI_SYSTEM);
	/* getaddrinfo */
	ret |= _getaddrinfo(progname);
	return ret;
}


/* gai_strerror */
static int _gai_strerror(char const * message, int value)
{
	printf("%s: %s\n", message, gai_strerror(value));
	return 0;
}


/* getaddrinfo */
static int _getaddrinfo(char const * progname)
{
	int ret = 0;
	struct addrinfo hints;
	struct addrinfo * ai;
	int res;
	struct addrinfo * p;
	struct sockaddr_in * sin;
	struct sockaddr_in6 * sin6;
	char buf[32];

	/* FIXME also test without hints and without AI_PASSIVE set */
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_flags = AI_PASSIVE;
	if((res = getaddrinfo("localhost", "http", &hints, &ai)) != 0)
	{
		fprintf(stderr, "%s: %s: %s\n", progname, "getaddrinfo",
				gai_strerror(res));
		return 1;
	}
	for(p = ai; p != NULL; p = p->ai_next)
		if(p->ai_family == AF_INET)
		{
			sin = (struct sockaddr_in *)p->ai_addr;
			/* FIXME also verify the address */
			if(sin->sin_port != 80)
				ret = 1;
			printf("%s: %s:%u%s\n", "localhost", inet_ntoa(
						sin->sin_addr),
					sin->sin_port,
					(ret == 0) ? "" : " (WRONG)");
		}
		else if(p->ai_family == AF_INET6)
		{
			sin6 = (struct sockaddr_in6 *)p->ai_addr;
			/* FIXME also verify the address */
			if(sin6->sin6_port != 80)
				ret = 1;
			printf("%s: %s:%u%s\n", "localhost", inet_ntop(
						p->ai_family, &sin6->sin6_addr,
						buf, sizeof(buf)),
					sin6->sin6_port,
					(ret == 0) ? "" : " (WRONG)");
		}
	freeaddrinfo(ai);
	return ret;
}


/* gethostbyaddr */
static int _gethostbyaddr(char const * addr, size_t length, int type)
{
	return (gethostbyaddr(addr, length, type) != NULL) ? 0 : 1;
}


/* gethostent */
static int _gethostent(void)
{
	struct hostent * he;
	unsigned int i;
	char * const * p;
	char const * sep;

	sethostent(1);
	for(i = 0; (he = gethostent()) != NULL; i++)
	{
		printf("%s\t%d %d", he->h_name, he->h_addrtype, he->h_length);
		if(he->h_aliases != NULL)
		{
			sep = "\t";
			for(p = he->h_aliases; *p != NULL; p++)
			{
				printf("%s%s", sep, *p);
				sep = ", ";
			}
		}
		putchar('\n');
	}
	endhostent();
	printf("%u hosts listed\n", i);
	return 0;
}


/* getnameinfo */
static int _getnameinfo(char const * progname)
{
	struct sockaddr_in sa;
	char node[16];
	char service[16];
	const int flags = 0;
	int res;

	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	sa.sin_port = 80;
	if((res = getnameinfo((struct sockaddr *)&sa, sizeof(sa),
					node, sizeof(node),
					service, sizeof(service), flags)) != 0)
	{
		fprintf(stderr, "%s: %s: %s\n", progname, "getnameinfo",
				gai_strerror(res));
		return 1;
	}
	if(strcmp(service, "http") != 0)
	{
		fprintf(stderr, "%s: %s: Wrong service (expected: %s)\n",
				progname, "getnameinfo", "http");
		return 1;
	}
	return 0;
}


/* getnetent */
static int _getnetent(void)
{
	struct netent * ne;
	unsigned int i;
	char * const * p;
	char const * sep;

	setnetent(1);
	for(i = 0; (ne = getnetent()) != NULL; i++)
	{
		printf("%s\t%d %u", ne->n_name, ne->n_addrtype, ne->n_net);
		if(ne->n_aliases != NULL)
		{
			sep = "\t";
			for(p = ne->n_aliases; *p != NULL; p++)
			{
				printf("%s%s", sep, *p);
				sep = ", ";
			}
		}
		putchar('\n');
	}
	endnetent();
	printf("%u networks listed\n", i);
	return 0;
}


/* getprotoent */
static int _getprotoent(void)
{
	struct protoent * pe;
	unsigned int i;
	char * const * p;
	char const * sep;

	setprotoent(1);
	for(i = 0; (pe = getprotoent()) != NULL; i++)
	{
		printf("%s\t%d", pe->p_name, pe->p_proto);
		if(pe->p_aliases != NULL)
		{
			sep = "\t";
			for(p = pe->p_aliases; *p != NULL; p++)
			{
				printf("%s%s", sep, *p);
				sep = ", ";
			}
		}
		putchar('\n');
	}
	endprotoent();
	printf("%u protocols listed\n", i);
	return 0;
}


/* getservbyname */
static int _getservbyname(char const * name, char const * protocol)
{
	struct servent * se;

	printf("%s: %s/%s\n", "getservbyname", name, protocol);
	if((se = getservbyname(name, protocol)) == NULL)
		return 0;
	printf("%s\t%d/%s\n", se->s_name, se->s_port, se->s_proto);
	return 0;
}


/* getservbyport */
static int _getservbyport(int port, char const * protocol)
{
	struct servent * se;

	printf("%s: %d/%s\n", "getservbyport", port, protocol);
	if((se = getservbyport(port, protocol)) == NULL)
		return 0;
	printf("%s\t%d/%s\n", se->s_name, se->s_port, se->s_proto);
	return 0;
}


/* getservent */
static int _getservent(void)
{
	struct servent * se;
	unsigned int i;
	char * const * p;

	printf("%s:\n", "getservent");
	setservent(1);
	for(i = 0; (se = getservent()) != NULL; i++)
	{
		printf("%s\t%d/%s", se->s_name, se->s_port, se->s_proto);
		if(se->s_aliases != NULL)
			for(p = se->s_aliases; *p != NULL; p++)
				printf(" %s", *p);
		putchar('\n');
	}
	endservent();
	printf("%u services listed\n", i);
	return 0;
}


/* hstrerror */
static int _hstrerror(char const * message, int value)
{
	printf("%s: %s\n", message, hstrerror(value));
	return 0;
}


/* main */
int main(int argc, char * argv[])
{
	int ret = 0;

	ret |= _netdb(argv[0]);
	return (ret == 0) ? 0 : 2;
}
