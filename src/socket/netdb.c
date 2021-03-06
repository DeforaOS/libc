/* $Id$ */
/* Copyright (c) 2008-2016 Pierre Pronchery <khorben@defora.org> */
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



#include "sys/types.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "strings.h"
#include "ctype.h"
#include "limits.h"
#include "errno.h"
#include "arpa/inet.h"
#include "netdb.h"


/* private */
/* constants */
#define ETC_HOSTS	"/etc/hosts"
#define ETC_NETWORKS	"/etc/networks"
#define ETC_PROTOCOLS	"/etc/protocols"
#define ETC_SERVICES	"/etc/services"


/* variables */
static FILE * _hostfp = NULL;
static FILE * _netfp = NULL;
static FILE * _protofp = NULL;
static FILE * _servfp = NULL;


/* prototypes */
static void _hostent_free(struct hostent * he);
static void _netent_free(struct netent * ne);
static void _protoent_free(struct protoent * pe);
static void _servent_free(struct servent * se);


/* public */
/* variables */
int h_errno = 0;


/* functions */
/* endhostent */
void endhostent(void)
{
	if(_hostfp != NULL)
		fclose(_hostfp);
	_hostfp = NULL;
}


/* endnetent */
void endnetent(void)
{
	if(_netfp != NULL)
		fclose(_netfp);
	_netfp = NULL;
}


/* endprotoent */
void endprotoent(void)
{
	if(_protofp != NULL)
		fclose(_protofp);
	_protofp = NULL;
}


/* endservent */
void endservent(void)
{
	if(_servfp != NULL)
		fclose(_servfp);
	_servfp = NULL;
}


/* freeaddrinfo */
void freeaddrinfo(struct addrinfo * ai)
{
	struct addrinfo * p;

	for(p = ai; p != NULL; p = ai)
	{
		ai = p->ai_next;
		free(p);
	}
}


/* gai_strerror */
const char * gai_strerror(int ecode)
{
	static const struct
	{
		const int errnum;
		const char * errmsg;
	} err[] =
	{
		{ 0,		"Success"				},
		{ EAI_AGAIN,	"Temporary failure in name resolution"	},
		{ EAI_BADFLAGS,	"Invalid value for the flags"		},
		{ EAI_FAIL,	"Non-recoverable error"			},
		{ EAI_FAMILY,	"Address family not recognized"		},
		{ EAI_MEMORY,	"Memory allocation failure"		},
		{ EAI_NONAME,	"The name did not resolve"		},
		{ EAI_OVERFLOW,	"Argument buffer overflowed"		},
		{ EAI_SERVICE,	"Service not recognized"		},
		{ EAI_SOCKTYPE,	"Socket type not recognized"		},
		{ EAI_SYSTEM,	"System error"				},
		{ -1,		NULL					}
	};
	unsigned int i;

	for(i = 0; err[i].errmsg != NULL; i++)
		if(err[i].errnum == ecode)
			return err[i].errmsg;
	return "Unknown error";
}


/* getaddrinfo */
static struct addrinfo * _getaddrinfo_alloc(int family, int socktype,
		int protocol, socklen_t addrlen, struct sockaddr * addr,
		struct addrinfo ** res);
static int _getaddrinfo_hints(struct addrinfo const * hints);
static int _getaddrinfo_nodename(char const * nodename,
		struct addrinfo const * hints, struct addrinfo ** res);
static int _getaddrinfo_nodename_default(struct addrinfo const * hints,
		struct addrinfo ** res);
static int _getaddrinfo_nodename_default_inet(struct addrinfo const * hints,
		struct addrinfo ** res);
static int _getaddrinfo_nodename_default_inet6(struct addrinfo const * hints,
		struct addrinfo ** res);
static int _getaddrinfo_nodename_files(char const * nodename,
		struct addrinfo const * hints, struct addrinfo ** res);
static int _getaddrinfo_nodename_files_inet(struct addrinfo const * hints,
		struct hostent * he, char ** addr, struct addrinfo ** res);
static int _getaddrinfo_nodename_files_inet6(struct addrinfo const * hints,
		struct hostent * he, char ** addr, struct addrinfo ** res);
static int _getaddrinfo_nodename_hosts_lookup(char const * nodename,
		struct hostent * he);
static int _getaddrinfo_nodename_numeric(char const * nodename,
		struct addrinfo const * hints, struct addrinfo ** res);
static int _getaddrinfo_servname(char const * servname,
		struct addrinfo const * hints, struct addrinfo ** res);
static int _getaddrinfo_servname_files(char const * servname,
		struct addrinfo const * hints, struct addrinfo ** res);
static int _getaddrinfo_servname_numeric(char const * servname,
		struct addrinfo ** res);
static int _getaddrinfo_servname_services_lookup(char const * servname,
		struct addrinfo const * hints, struct servent * se);

int getaddrinfo(char const * nodename, char const * servname,
		struct addrinfo const * hints, struct addrinfo ** res)
{
	int ret;
	struct addrinfo h;

	if(nodename == NULL && servname == NULL)
		return EAI_NONAME;
	if(hints == NULL)
	{
		memset(&h, 0, sizeof(h));
		h.ai_family = AF_UNSPEC;
		hints = &h;
	}
	if((ret = _getaddrinfo_hints(hints)) != 0)
		return ret;
	*res = NULL;
	if((ret = _getaddrinfo_nodename(nodename, hints, res)) != 0
			|| (ret = _getaddrinfo_servname(servname, hints,
					res)) != 0)
		freeaddrinfo(*res);
	return ret;
}

static struct addrinfo * _getaddrinfo_alloc(int family, int socktype,
		int protocol, socklen_t addrlen, struct sockaddr * addr,
		struct addrinfo ** res)
{
	struct addrinfo * ret;
	struct addrinfo * p;

	if((ret = malloc(sizeof(*ret) + addrlen)) == NULL)
		return NULL;
	memset(ret, 0, sizeof(*ret));
	ret->ai_family = family;
	ret->ai_socktype = socktype;
	ret->ai_protocol = protocol;
	ret->ai_addrlen = addrlen;
	ret->ai_addr = (struct sockaddr *)(ret + 1);
	memcpy(ret->ai_addr, addr, addrlen);
	if(*res == NULL)
		*res = ret;
	else
	{
		for(p = *res; p->ai_next != NULL; p = p->ai_next);
		p->ai_next = ret;
	}
	return ret;
}

static int _getaddrinfo_hints(struct addrinfo const * hints)
{
	switch(hints->ai_family)
	{
		case AF_INET:
		case AF_UNSPEC:
			break;
		default:
			/* unknown family */
			return EAI_FAMILY;
	}
	switch(hints->ai_socktype)
	{
		case 0:
		case SOCK_DGRAM:
		case SOCK_RAW:
		case SOCK_STREAM:
			break;
		default:
			/* unknown socket type */
			return EAI_SOCKTYPE;
	}
	return 0;
}

static int _getaddrinfo_nodename(char const * nodename,
		struct addrinfo const * hints, struct addrinfo ** res)
{
	int ret = -1;

	if(nodename == NULL)
		return _getaddrinfo_nodename_default(hints, res);
	if(hints->ai_flags & AI_NUMERICHOST)
		return _getaddrinfo_nodename_numeric(nodename, hints, res);
	/* FIXME implement more */
	ret = _getaddrinfo_nodename_files(nodename, hints, res);
	if(ret != 0 && _getaddrinfo_nodename_numeric(nodename, hints, res) == 0)
		ret = 0;
	return ret;
}

static int _getaddrinfo_nodename_default(struct addrinfo const * hints,
		struct addrinfo ** res)
{
	switch(hints->ai_family)
	{
		case AF_UNSPEC:
			/* fallback */
		case AF_INET:
			return _getaddrinfo_nodename_default_inet(hints, res);
		case AF_INET6:
			return _getaddrinfo_nodename_default_inet6(hints, res);
		default:
			return EAI_FAMILY;
	}
}

static int _getaddrinfo_nodename_default_inet(struct addrinfo const * hints,
		struct addrinfo ** res)
{
	int passive = (hints->ai_flags & AI_PASSIVE) ? 1 : 0;
	struct sockaddr_in sin;

	memset(&sin, 0, sizeof(sin));
	sin.sin_addr.s_addr = passive ? INADDR_ANY : INADDR_LOOPBACK;
	if(_getaddrinfo_alloc(AF_INET, hints->ai_socktype, hints->ai_protocol,
				sizeof(sin), (struct sockaddr *)&sin, res)
			== NULL)
		return EAI_MEMORY;
	return 0;
}

static int _getaddrinfo_nodename_default_inet6(struct addrinfo const * hints,
		struct addrinfo ** res)
{
	int passive = (hints->ai_flags & AI_PASSIVE) ? 1 : 0;
	struct sockaddr_in6 sin6;
	const char sin6_addr_any[] = IN6ADDR_ANY_INIT;
	const char sin6_addr_loopback[] = IN6ADDR_LOOPBACK_INIT;

	memset(&sin6, 0, sizeof(sin6));
	memcpy(sin6.sin6_addr.s6_addr,
			passive ? sin6_addr_any : sin6_addr_loopback,
			sizeof(sin6.sin6_addr.s6_addr));
	if(_getaddrinfo_alloc(AF_INET6, hints->ai_socktype, hints->ai_protocol,
				sizeof(sin6), (struct sockaddr *)&sin6, res)
			== NULL)
		return EAI_MEMORY;
	return 0;
}

static int _getaddrinfo_nodename_files(char const * nodename,
		struct addrinfo const * hints, struct addrinfo ** res)
{
	struct hostent * he;
	char ** addr;
	int ret;

	/* XXX may have side-effects */
	sethostent(1);
	while((he = gethostent()) != NULL)
	{
		if(_getaddrinfo_nodename_hosts_lookup(nodename, he) != 0)
			continue;
		if(hints->ai_family != AF_UNSPEC
				&& hints->ai_family != he->h_addrtype)
			continue;
		for(addr = he->h_addr_list; *addr != NULL; addr++)
			switch(he->h_addrtype)
			{
				case AF_INET6:
					ret = _getaddrinfo_nodename_files_inet6(
							hints, he, addr, res);
					if(ret != 0)
						return ret;
					break;
				case AF_INET:
					ret = _getaddrinfo_nodename_files_inet(
							hints, he, addr, res);
					if(ret != 0)
						return ret;
					break;
			}
		return 0;
	}
	return EAI_NONAME;
}

static int _getaddrinfo_nodename_files_inet(struct addrinfo const * hints,
		struct hostent * he, char ** addr, struct addrinfo ** res)
{
	struct sockaddr_in sin;

	if(sizeof(sin.sin_addr.s_addr) != he->h_length)
		return EAI_SYSTEM;
	memset(&sin, 0, sizeof(sin));
	memcpy(&sin.sin_addr.s_addr, *addr, sizeof(sin.sin_addr.s_addr));
	if(_getaddrinfo_alloc(he->h_addrtype, hints->ai_socktype,
				hints->ai_protocol, sizeof(sin),
				(struct sockaddr *)&sin, res) == NULL)
		return EAI_MEMORY;
	return 0;
}

static int _getaddrinfo_nodename_files_inet6(struct addrinfo const * hints,
		struct hostent * he, char ** addr, struct addrinfo ** res)
{
	struct sockaddr_in6 sin6;

	if(sizeof(sin6.sin6_addr.s6_addr) != he->h_length)
		return EAI_SYSTEM;
	memset(&sin6, 0, sizeof(sin6));
	memcpy(&sin6.sin6_addr.s6_addr, *addr, sizeof(sin6.sin6_addr.s6_addr));
	if(_getaddrinfo_alloc(he->h_addrtype, hints->ai_socktype,
				hints->ai_protocol, sizeof(sin6),
				(struct sockaddr *)&sin6, res) == NULL)
		return EAI_MEMORY;
	return 0;
}

static int _getaddrinfo_nodename_hosts_lookup(char const * nodename,
		struct hostent * he)
{
	char ** alias;

	if(strcasecmp(he->h_name, nodename) == 0)
		return 0;
	if(he->h_aliases != NULL)
		for(alias = he->h_aliases; *alias != NULL; alias++)
			if(strcasecmp(*alias, nodename) == 0)
				return 0;
	return -1;
}

static int _getaddrinfo_nodename_numeric(char const * nodename,
		struct addrinfo const * hints, struct addrinfo ** res)
{
	struct sockaddr_in sin;

	switch(hints->ai_family)
	{
		case AF_UNSPEC:
			/* fallback */
		case AF_INET:
			memset(&sin, 0, sizeof(sin));
			if(inet_aton(nodename, &sin.sin_addr) != 1)
				break;
			if(_getaddrinfo_alloc(AF_INET, hints->ai_socktype,
						hints->ai_protocol, sizeof(sin),
						(struct sockaddr *)&sin, res)
					== NULL)
				return EAI_MEMORY;
			return 0;
		case AF_INET6:
			/* FIXME implement */
		default:
			return EAI_FAMILY;
	}
	return EAI_FAIL;
}

static int _getaddrinfo_servname(char const * servname,
		struct addrinfo const * hints, struct addrinfo ** res)
{
	int ret = -1;

	if(servname == NULL)
		return 0;
	if(hints->ai_flags & AI_NUMERICSERV)
		return _getaddrinfo_servname_numeric(servname, res);
	ret = _getaddrinfo_servname_files(servname, hints, res);
	if(ret != 0 && _getaddrinfo_servname_numeric(servname, res) == 0)
		ret = 0;
	return ret;
}

static int _getaddrinfo_servname_files(char const * servname,
		struct addrinfo const * hints, struct addrinfo ** res)
{
	struct servent * se;
	struct addrinfo * ai;
	struct sockaddr_in * sin;
	struct sockaddr_in6 * sin6;

	/* XXX may have side-effects */
	setservent(1);
	while((se = getservent()) != NULL)
	{
		if(_getaddrinfo_servname_services_lookup(servname, hints, se)
				!= 0)
			continue;
		for(ai = *res; ai != NULL; ai = ai->ai_next)
			if(ai->ai_family == AF_INET6)
			{
				sin6 = (struct sockaddr_in6 *)ai->ai_addr;
				sin6->sin6_port = se->s_port;
			}
			else if(ai->ai_family == AF_INET)
			{
				sin = (struct sockaddr_in *)ai->ai_addr;
				sin->sin_port = se->s_port;
			}
		return 0;
	}
	return EAI_NONAME;
}

static int _getaddrinfo_servname_numeric(char const * servname,
		struct addrinfo ** res)
{
	int ret = 0;
	int e;
	unsigned long u;
	char * p;
	struct addrinfo * ai;
	struct sockaddr_in * sin;
	struct sockaddr_in6 * sin6;

	if(!isdigit((int)(unsigned char const)*servname))
		return -1;
	e = errno;
	errno = 0;
	u = strtoul(servname, &p, 10);
	/* XXX ports may have different constraints besides AF_INET */
	if(errno == 0 && *p == '\0' && u <= 65535)
	{
		for(ai = *res; ai != NULL; ai = ai->ai_next)
			if(ai->ai_family == AF_INET6)
			{
				sin6 = (struct sockaddr_in6 *)ai->ai_addr;
				sin6->sin6_port = u;
			}
			else if(ai->ai_family == AF_INET)
			{
				sin = (struct sockaddr_in *)ai->ai_addr;
				sin->sin_port = u;
			}
	}
	else
		ret = -1;
	errno = e;
	return ret;
}

static int _getaddrinfo_servname_services_lookup(char const * servname,
		struct addrinfo const * hints, struct servent * se)
{
	char ** alias;
	struct protoent * pe;

	pe = getprotobyname(se->s_proto);
	if(strcasecmp(se->s_name, servname) != 0)
	{
		if(se->s_aliases == NULL)
			return -1;
		for(alias = se->s_aliases; *alias != NULL; alias++)
			if(strcasecmp(*alias, servname) == 0)
				break;
		if(*alias == NULL)
			return -1;
	}
	if(hints->ai_protocol == 0)
		return 0;
	if((pe = getprotobyname(se->s_proto)) == NULL)
		return -1;
	return (pe->p_proto == hints->ai_protocol) ? 0 : -1;
}


/* gethostbyaddr */
struct hostent * gethostbyaddr(const void * addr, socklen_t len, int type)
{
	struct hostent * he;
	char ** p;

	sethostent(1);
	while((he = gethostent()) != NULL)
		if(he->h_addrtype == type && he->h_length == len)
			for(p = &he->h_addr_list[0]; *p != NULL; p++)
				if(memcmp(*p, addr, len) == 0)
					return he;
	return NULL;
}


/* gethostbyname */
struct hostent * gethostbyname(const char * name)
{
	static struct hostent ret = { NULL, NULL, 0, 0, NULL };
	struct hostent * he;
	struct addrinfo hints;
	struct addrinfo * ai;

	sethostent(1);
	while((he = gethostent()) != NULL)
		if(strcmp(he->h_name, name) == 0)
			return he;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	if(getaddrinfo(name, NULL, &hints, &ai) != 0)
		return NULL;
	_hostent_free(&ret);
	ret.h_name = strdup(name);
	ret.h_aliases = NULL;
	ret.h_addrtype = ai->ai_family;
	ret.h_length = ai->ai_addrlen;
	if((ret.h_addr_list = malloc(2 * sizeof(*ret.h_addr_list))) != NULL)
	{
		if((ret.h_addr_list[0] = malloc(ai->ai_addrlen)) != NULL)
			memcpy(ret.h_addr_list[0], ai->ai_addr, ai->ai_addrlen);
		ret.h_addr_list[1] = NULL;
	}
	freeaddrinfo(ai);
	/* check for errors */
	if(ret.h_name == NULL || ret.h_addr_list == NULL
			|| ret.h_addr_list[0] == NULL)
	{
		_hostent_free(&ret);
		return NULL;
	}
	return &ret;
}


/* gethostent */
static char * _gethostent_addr(char const ** s);
static int _gethostent_alias(struct hostent * he, char * alias);
static char * _gethostent_host(char const ** s);

struct hostent * gethostent(void)
{
	static struct hostent he = { NULL, NULL, 0, 0, NULL };
	char buf[512];
	char const * s;
	char * p;

	if(_hostfp == NULL)
		sethostent(1);
	if(_hostfp == NULL)
		return NULL;
	for(;;)
	{
		_hostent_free(&he);
		if(fgets(buf, sizeof(buf), _hostfp) == NULL)
			break;
		/* skip whitespaces */
		for(s = buf; isspace(*s); s++);
		/* skip comments */
		if(*s == '#' || *s == '\0')
			continue;
		/* read address */
		if((he.h_addr_list = malloc(2 * sizeof(*he.h_addr_list)))
				== NULL)
			continue;
		he.h_addr_list[1] = NULL;
		if((he.h_addr_list[0] = _gethostent_addr(&s)) == NULL)
			continue;
		if(!isspace(*s))
			continue;
		/* skip whitespaces */
		for(s++; isspace(*s); s++);
		/* read hostname */
		if((he.h_name = _gethostent_host(&s)) == NULL)
			continue;
		/* skip whitespaces */
		for(; isspace(*s); s++);
		/* read optional aliases */
		while((p = _gethostent_host(&s)) != NULL)
		{
			_gethostent_alias(&he, p);
			for(; isspace(*s); s++);
		}
		/* return entry */
		he.h_addrtype = AF_INET;
		he.h_length = 4;
		return &he;
	}
	/* nothing found */
	endhostent();
	return NULL;
}

static char * _gethostent_addr(char const ** s)
{
	char * ret;
	const size_t len = 4;
	int e;
	size_t i;
	unsigned long u;
	char * p = NULL;

	if((ret = malloc(len * sizeof(*ret))) == NULL)
		return NULL;
	e = errno;
	errno = 0;
	for(i = 0; i < len; i++)
	{
		if(**s == '\0' || **s < '0' || **s > '9')
			break;
		u = strtoul(*s, &p, 10);
		*s = p;
		if(errno != 0 || u > 255)
			break;
		ret[i] = u;
		if(i == len - 1)
		{
			errno = e;
			return ret;
		}
		if(*p != '.')
			break;
		(*s)++;
	}
	free(ret);
	errno = e;
	return NULL;
}

static int _gethostent_alias(struct hostent * he, char * alias)
{
	char ** p;
	size_t cnt = 0;

	if(he->h_aliases != NULL)
		for(; he->h_aliases[cnt] != NULL; cnt++);
	if((p = realloc(he->h_aliases, sizeof(*p) * (cnt + 2))) == NULL)
	{
		free(alias);
		return -1;
	}
	he->h_aliases = p;
	he->h_aliases[cnt++] = alias;
	he->h_aliases[cnt] = NULL;
	return 0;
}

static char * _gethostent_host(char const ** s)
{
	char * ret = NULL;
	size_t len = 0;
	char * p;

	for(; isalnum((int)(unsigned char)**s) || **s == '-' || **s == '.';
			(*s)++)
	{
		/* XXX only realloc() once */
		if((p = realloc(ret, len + 2)) == NULL)
		{
			free(ret);
			return NULL;
		}
		ret = p;
		p[len++] = **s;
	}
	if(len == 0)
		return NULL;
	ret[len] = '\0';
	return ret;
}


/* getnameinfo */
static int _getnameinfo_inet(const struct sockaddr_in * sa, socklen_t salen,
		char * node, socklen_t nodelen,
		char * service, socklen_t servicelen, int flags);
static int _getnameinfo_inet6(const struct sockaddr_in6 * sa, socklen_t salen,
		char * node, socklen_t nodelen,
		char * service, socklen_t servicelen, int flags);
static int _getnameinfo_node(const void * addr, socklen_t len, int type,
		char * node, socklen_t nodelen);
static int _getnameinfo_service(int port, char * service, socklen_t servicelen,
		int flags);

int getnameinfo(const struct sockaddr * sa, socklen_t salen, char * node,
		socklen_t nodelen, char * service, socklen_t servicelen,
		int flags)
{
	if(sa == NULL)
	{
		errno = EINVAL;
		return EAI_SYSTEM;
	}
	switch(sa->sa_family)
	{
		case AF_INET:
			return _getnameinfo_inet((struct sockaddr_in *)sa,
					salen, node, nodelen,
					service, servicelen, flags);
		case AF_INET6:
			return _getnameinfo_inet6((struct sockaddr_in6 *)sa,
					salen, node, nodelen,
					service, servicelen, flags);
		default:
			return EAI_FAMILY;
	}
}

static int _getnameinfo_inet(const struct sockaddr_in * sa, socklen_t salen,
		char * node, socklen_t nodelen,
		char * service, socklen_t servicelen, int flags)
{
	int ret = 0;

	if(salen < (socklen_t)sizeof(*sa))
	{
		errno = EINVAL;
		return EAI_SYSTEM;
	}
	if(nodelen > 0)
	{
		if((flags & NI_NUMERICHOST) == 0)
			ret = _getnameinfo_node(&sa->sin_addr.s_addr,
					sizeof(sa->sin_addr.s_addr),
					sa->sin_family, node, nodelen);
		else
			ret = EAI_NONAME;
		if(ret == EAI_NONAME && (flags & NI_NAMEREQD) == 0
				&& inet_ntop(sa->sin_family, &sa->sin_addr,
					node, nodelen) != NULL)
			ret = 0;
	}
	if(ret == 0 && servicelen > 0)
		ret = _getnameinfo_service(sa->sin_port, service, servicelen,
				flags);
	return ret;
}

static int _getnameinfo_inet6(const struct sockaddr_in6 * sa, socklen_t salen,
		char * node, socklen_t nodelen,
		char * service, socklen_t servicelen, int flags)
{
	int ret = 0;

	if(salen < (socklen_t)sizeof(*sa))
	{
		errno = EINVAL;
		return EAI_SYSTEM;
	}
	if(nodelen > 0)
	{
		if((flags & NI_NUMERICHOST) == 0)
			ret = _getnameinfo_node(&sa->sin6_addr.s6_addr,
					sizeof(sa->sin6_addr.s6_addr),
					sa->sin6_family, node, nodelen);
		else
			ret = EAI_NONAME;
		if(ret == EAI_NONAME && (flags & NI_NAMEREQD) == 0
				&& inet_ntop(sa->sin6_family, &sa->sin6_addr,
					node, nodelen) != NULL)
			ret = 0;
	}
	if(ret == 0 && servicelen > 0)
		ret = _getnameinfo_service(sa->sin6_port, service, servicelen,
				flags);
	return ret;
}

static int _getnameinfo_node(const void * addr, socklen_t len, int type,
		char * node, socklen_t nodelen)
{
	struct hostent * he = NULL;

	if((he = gethostbyaddr(addr, len, type)) == NULL)
		switch(h_errno)
		{
			case TRY_AGAIN:
				return EAI_AGAIN;
			case NO_RECOVERY:
				return EAI_FAIL;
			case HOST_NOT_FOUND:
			case NO_DATA:
				/* fallback */
			default:
				return EAI_NONAME;
		}
	if(snprintf(NULL, 0, "%s", he->h_name) >= nodelen)
		return EAI_SYSTEM;
	snprintf(node, nodelen, "%s", he->h_name);
	return 0;
}

static int _getnameinfo_service(int port, char * service, socklen_t servicelen,
		int flags)
{
	char const * proto = (flags & NI_DGRAM) ? "udp" : "tcp";
	struct servent * se;

	if((se = getservbyport(port, proto)) == NULL)
		return EAI_NONAME;
	/* FIXME check that it fits */
	if(flags & NI_NUMERICSERV)
		snprintf(service, servicelen, "%d", se->s_port);
	else
		snprintf(service, servicelen, "%s", se->s_name);
	return 0;
}


/* getnetbyaddr */
struct netent * getnetbyaddr(uint32_t net, int type)
{
	struct netent * ne;

	setnetent(1);
	while((ne = getnetent()) != NULL)
		if(ne->n_net == net && ne->n_addrtype == type)
			return ne;
	return NULL;
}


/* getnetbyname */
struct netent * getnetbyname(const char * name)
{
	struct netent * ne;

	setnetent(1);
	while((ne = getnetent()) != NULL)
		if(strcmp(ne->n_name, name) == 0)
			return ne;
	return NULL;
}


/* getnetent */
static int _getnetent_alias(struct netent * ne, char * alias);
static char * _getnetent_name(char const ** s);
static int _getnetent_net(uint32_t * net, char const ** s);

struct netent * getnetent(void)
{
	static struct netent ne = { NULL, NULL, 0, 0 };
	char buf[512];
	char const * s;
	char * p;

	if(_netfp == NULL)
		setnetent(1);
	if(_netfp == NULL)
		return NULL;
	for(;;)
	{
		_netent_free(&ne);
		if(fgets(buf, sizeof(buf), _netfp) == NULL)
			break;
		/* skip whitespaces */
		for(s = buf; isspace(*s); s++);
		/* skip comments */
		if(*s == '#' || *s == '\0')
			continue;
		/* read name */
		if((ne.n_name = _getnetent_name(&s)) == NULL)
			continue;
		if(!isspace(*s))
			continue;
		/* skip whitespaces */
		for(s++; isspace(*s); s++);
		/* read network */
		if(_getnetent_net(&ne.n_net, &s) != 0)
			continue;
		/* skip whitespaces */
		for(; isspace(*s); s++);
		/* read optional aliases */
		while((p = _getnetent_name(&s)) != NULL)
		{
			_getnetent_alias(&ne, p);
			for(; isspace(*s); s++);
		}
		ne.n_addrtype = AF_INET;
		return &ne;
	}
	endnetent();
	return NULL;
}

static int _getnetent_alias(struct netent * ne, char * alias)
{
	char ** p;
	size_t cnt = 0;

	if(ne->n_aliases != NULL)
		for(; ne->n_aliases[cnt] != NULL; cnt++);
	if((p = realloc(ne->n_aliases, sizeof(*p) * (cnt + 2))) == NULL)
	{
		free(alias);
		return -1;
	}
	ne->n_aliases = p;
	ne->n_aliases[cnt++] = alias;
	ne->n_aliases[cnt] = NULL;
	return 0;
}

static char * _getnetent_name(char const ** s)
{
	char * ret = NULL;
	size_t len = 0;
	char * p;

	for(; isalnum((int)(unsigned char)**s) || **s == '-' || **s == '.';
			(*s)++)
	{
		/* XXX only realloc() once */
		if((p = realloc(ret, len + 2)) == NULL)
		{
			free(ret);
			return NULL;
		}
		ret = p;
		p[len++] = **s;
	}
	if(len == 0)
		return NULL;
	ret[len] = '\0';
	return ret;
}

static int _getnetent_net(uint32_t * net, char const ** s)
{
	int ret = 0;
	int e;
	uint32_t u;
	char * p;

	if(!isdigit((int)(unsigned char)**s))
		return -1;
	e = errno;
	errno = 0;
	u = strtoul(*s, &p, 10);
	if(errno == 0)
	{
		*net = u;
		*s = p;
	}
	else
		ret = -1;
	errno = e;
	return ret;
}


/* getprotobyname */
struct protoent * getprotobyname(const char * name)
{
	struct protoent * pe;

	setprotoent(1);
	while((pe = getprotoent()) != NULL)
		if(strcmp(pe->p_name, name) == 0)
			return pe;
	return NULL;
}


/* getprotobynumber */
struct protoent * getprotobynumber(int proto)
{
	struct protoent * pe;

	setprotoent(1);
	while((pe = getprotoent()) != NULL)
		if(pe->p_proto == proto)
			return pe;
	return NULL;
}


/* getprotoent */
static int _getprotoent_alias(struct protoent * pe, char * alias);
static char * _getprotoent_name(char const ** s);
static int _getprotoent_proto(int * proto, char const ** s);

struct protoent * getprotoent(void)
{
	static struct protoent pe = { NULL, NULL, 0 };
	char buf[512];
	char const * s;
	char * p;

	if(_protofp == NULL)
		setprotoent(1);
	if(_protofp == NULL)
		return NULL;
	for(;;)
	{
		_protoent_free(&pe);
		if(fgets(buf, sizeof(buf), _protofp) == NULL)
			break;
		/* skip whitespaces */
		for(s = buf; isspace(*s); s++);
		/* skip comments */
		if(*s == '#' || *s == '\0')
			continue;
		/* read name */
		if((pe.p_name = _getprotoent_name(&s)) == NULL)
			continue;
		if(!isspace(*s))
			continue;
		/* skip whitespaces */
		for(s++; isspace(*s); s++);
		/* read protocol */
		if(_getprotoent_proto(&pe.p_proto, &s) != 0)
			continue;
		/* skip whitespaces */
		for(; isspace(*s); s++);
		/* read optional aliases */
		while((p = _getprotoent_name(&s)) != NULL)
		{
			_getprotoent_alias(&pe, p);
			for(; isspace(*s); s++);
		}
		return &pe;
	}
	endprotoent();
	return NULL;
}

static int _getprotoent_alias(struct protoent * pe, char * alias)
{
	char ** p;
	size_t cnt = 0;

	if(pe->p_aliases != NULL)
		for(; pe->p_aliases[cnt] != NULL; cnt++);
	if((p = realloc(pe->p_aliases, sizeof(*p) * (cnt + 2))) == NULL)
	{
		free(alias);
		return -1;
	}
	pe->p_aliases = p;
	pe->p_aliases[cnt++] = alias;
	pe->p_aliases[cnt] = NULL;
	return 0;
}

static char * _getprotoent_name(char const ** s)
{
	char * ret = NULL;
	size_t len = 0;
	char * p;

	for(; isalnum((int)(unsigned char)**s) || **s == '-' || **s == '.';
			(*s)++)
	{
		/* XXX only realloc() once */
		if((p = realloc(ret, len + 2)) == NULL)
		{
			free(ret);
			return NULL;
		}
		ret = p;
		p[len++] = **s;
	}
	if(len == 0)
		return NULL;
	ret[len] = '\0';
	return ret;
}

static int _getprotoent_proto(int * proto, char const ** s)
{
	int ret = 0;
	int e;
	int i;
	char * p;

	if(!isdigit((int)(unsigned char)**s))
		return -1;
	e = errno;
	errno = 0;
	i = strtol(*s, &p, 10);
	if(errno == 0)
	{
		*proto = i;
		*s = p;
	}
	else
		ret = -1;
	errno = e;
	return ret;
}


/* getservent */
static int _getservent_alias(struct servent * se, char * alias);
static char * _getservent_name(char const ** s);

struct servent * getservent(void)
{
	static struct servent se = { NULL, NULL, 0, NULL };
	char buf[512];
	char const * s;
	char * p;

	if(_servfp == NULL)
		setservent(1);
	if(_servfp == NULL)
		return NULL;
	for(;;)
	{
		_servent_free(&se);
		if(fgets(buf, sizeof(buf), _servfp) == NULL)
			break;
		/* skip whitespaces */
		for(s = buf; isspace(*s); s++);
		/* skip comments */
		if(*s == '#' || *s == '\0')
			continue;
		/* read service */
		if((se.s_name = _getservent_name(&s)) == NULL)
			continue;
		if(!isspace(*s))
			continue;
		/* skip whitespaces */
		for(s++; isspace(*s); s++);
		/* read port */
		se.s_port = strtol(s, &p, 10);
		if(*s == '\0' || *p != '/')
			continue;
		/* read protocol */
		s = p + 1;
		if((se.s_proto = _getservent_name(&s)) == NULL)
			continue;
		/* skip whitespaces */
		for(; isspace(*s); s++);
		/* read optional aliases */
		while((p = _getservent_name(&s)) != NULL)
		{
			_getservent_alias(&se, p);
			for(; isspace(*s); s++);
		}
		return &se;
	}
	/* nothing found */
	endservent();
	return NULL;
}

static int _getservent_alias(struct servent * se, char * alias)
{
	char ** p;
	size_t cnt = 0;

	if(se->s_aliases != NULL)
		for(; se->s_aliases[cnt] != NULL; cnt++);
	if((p = realloc(se->s_aliases, sizeof(*p) * (cnt + 2))) == NULL)
	{
		free(alias);
		return -1;
	}
	se->s_aliases = p;
	se->s_aliases[cnt++] = alias;
	se->s_aliases[cnt] = NULL;
	return 0;
}

static char * _getservent_name(char const ** s)
{
	char * ret = NULL;
	size_t len = 0;
	char * p;

	for(; isalnum((int)(unsigned char)**s) || **s == '-' || **s == '.';
			(*s)++)
	{
		/* XXX only realloc() once */
		if((p = realloc(ret, len + 2)) == NULL)
		{
			free(ret);
			return NULL;
		}
		ret = p;
		p[len++] = **s;
	}
	if(len == 0)
		return NULL;
	ret[len] = '\0';
	return ret;
}


/* getservbyname */
struct servent * getservbyname(const char * name, const char * protocol)
{
	struct servent * se;
	char * const * p;

	setservent(1);
	while((se = getservent()) != NULL)
		if(protocol != NULL && strcmp(se->s_proto, protocol) != 0)
			continue;
		else if(strcmp(se->s_name, name) == 0)
			return se;
		else if(se->s_aliases != NULL)
			for(p = se->s_aliases; *p != NULL; p++)
				if(strcmp(*p, name) == 0)
					return se;
	return NULL;
}


/* getservbyport */
struct servent * getservbyport(int port, const char * protocol)
{
	struct servent * se;

	setservent(1);
	while((se = getservent()) != NULL)
		if(protocol != NULL && strcmp(se->s_proto, protocol) != 0)
			continue;
		else if(se->s_port == port)
			return se;
	return NULL;
}


/* hstrerror */
char * hstrerror(int errnum)
{
	static char ret[256];
	static const struct
	{
		const int errnum;
		const char * errmsg;
	} err[] =
	{
		{ 0,			"Success"			},
		{ HOST_NOT_FOUND,	"Host not found"		},
		{ NO_DATA,		"No data"			},
		{ NO_RECOVERY,		"No recovery"			},
		{ TRY_AGAIN,		"Try again"			},
		{ -1,			NULL				}
	};
	unsigned int i;

	for(i = 0; err[i].errmsg != NULL; i++)
		if(err[i].errnum == errnum)
		{
			snprintf(ret, sizeof(ret), "%s", err[i].errmsg);
			return ret;
		}
	snprintf(ret, sizeof(ret), "%s%d", "Unknown error: ", errnum);
	return ret;
}


/* sethostent */
void sethostent(int stayopen)
{
	if(stayopen == 0)
		endhostent();
	else if(_hostfp != NULL)
	{
		if(fseek(_hostfp, 0, SEEK_SET) != 0)
			endhostent();
	}
	else if((_hostfp = fopen(ETC_HOSTS, "r")) == NULL)
		h_errno = NO_DATA;
}


/* setnetent */
void setnetent(int stayopen)
{
	if(stayopen == 0)
		endnetent();
	else if(_netfp != NULL)
	{
		if(fseek(_netfp, 0, SEEK_SET) != 0)
			endnetent();
	}
	else
		/* we can ignore errors */
		_netfp = fopen(ETC_NETWORKS, "r");
}


/* setprotoent */
void setprotoent(int stayopen)
{
	if(stayopen == 0)
		endprotoent();
	else if(_protofp != NULL)
	{
		if(fseek(_protofp, 0, SEEK_SET) != 0)
			endprotoent();
	}
	else
		/* we can ignore errors */
		_protofp = fopen(ETC_PROTOCOLS, "r");
}


/* setservent */
void setservent(int stayopen)
{
	if(stayopen == 0)
		endservent();
	else if(_servfp != NULL)
	{
		if(fseek(_servfp, 0, SEEK_SET) != 0)
			endservent();
	}
	else
		/* we can ignore errors */
		_servfp = fopen(ETC_SERVICES, "r");
}


/* private */
/* functions */
/* hostent_free */
static void _hostent_free(struct hostent * he)
{
	char ** p;

	free(he->h_name);
	if(he->h_aliases != NULL)
		for(p = he->h_aliases; *p != NULL; p++)
			free(*p);
	free(he->h_aliases);
	for(p = he->h_addr_list; p != NULL && *p != NULL; p++)
		free(*p);
	free(he->h_addr_list);
	memset(he, 0, sizeof(*he));
}


/* netent_free */
static void _netent_free(struct netent * ne)
{
	char ** p;

	free(ne->n_name);
	if(ne->n_aliases != NULL)
		for(p = ne->n_aliases; *p != NULL; p++)
			free(*p);
	free(ne->n_aliases);
	memset(ne, 0, sizeof(*ne));
}


/* protoent_free */
static void _protoent_free(struct protoent * pe)
{
	char ** p;

	free(pe->p_name);
	if(pe->p_aliases != NULL)
		for(p = pe->p_aliases; *p != NULL; p++)
			free(*p);
	free(pe->p_aliases);
	memset(pe, 0, sizeof(*pe));
}


/* servent_free */
static void _servent_free(struct servent * se)
{
	char ** p;

	free(se->s_name);
	if(se->s_aliases != NULL)
		for(p = se->s_aliases; *p != NULL; p++)
			free(*p);
	free(se->s_aliases);
	free(se->s_proto);
	memset(se, 0, sizeof(*se));
}
