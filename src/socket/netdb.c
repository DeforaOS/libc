/* $Id$ */
/* Copyright (c) 2008-2012 Pierre Pronchery <khorben@defora.org> */
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



#include "sys/types.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "ctype.h"
#include "errno.h"
#include "netdb.h"


/* private */
/* variables */
static FILE * _fp = NULL;
static char _buf[512];


/* prototypes */
static void _hostent_free(struct hostent * he);


/* public */
/* variables */
int h_errno = 0;


/* functions */
/* endhostent */
void endhostent(void)
{
	if(_fp != NULL)
		fclose(_fp);
	_fp = NULL;
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


/* getaddrinfo */
int getaddrinfo(char const * nodename, char const * servname,
		struct addrinfo const * hints, struct addrinfo ** res)
{
	/* FIXME really implement */
	errno = ENOSYS;
	return -1;
}


/* gethostbyaddr */
struct hostent * gethostbyaddr(const void * addr, socklen_t len, int type)
{
	/* FIXME implement */
	errno = ENOSYS;
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
		ret.h_addr_list[1] = 0;
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


/* getservbyname */
struct servent * getservbyname(const char * name, const char * protocol)
{
	/* FIXME implement */
	errno = ENOSYS;
	return NULL;
}


/* gethostent */
static int _gethostent_open(void);
static char * _gethostent_addr(char const ** s);
static char * _gethostent_host(char const ** s);

struct hostent * gethostent(void)
{
	static struct hostent he = { NULL, NULL, 0, 0, NULL };
	char const * s;

	if(_gethostent_open() != 0)
		return NULL;
	for(;;)
	{
		_hostent_free(&he);
		if(fgets(_buf, sizeof(_buf), _fp) == NULL)
			break;
		/* skip whitespaces */
		for(s = _buf; isspace(*s); s++);
		/* skip comments */
		if(*s == '#' || *s == '\n')
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
		for(; isspace(*s); s++);
		/* read hostname */
		if((he.h_name = _gethostent_host(&s)) == NULL)
			continue;
		/* read optional aliases */
		/* FIXME implement */
		/* return entry */
		he.h_aliases = NULL;
		he.h_addrtype = AF_INET;
		he.h_length = 4;
		return &he;
	}
	/* nothing found */
	endhostent();
	return NULL;
}

static int _gethostent_open(void)
{
	if(_fp != NULL)
		return 0;
	sethostent(1);
	if(_fp != NULL)
		return 0;
	return -1;
}

static char * _gethostent_addr(char const ** s)
{
	char * ret;
	int i;
	unsigned long u;
	char * p = NULL;

	if((ret = malloc(4 * sizeof(char))) == NULL)
		return NULL;
	for(i = 0; i < 4; i++)
	{
		if(**s == '\0' || **s < '0' || **s > '9')
			break;
		errno = 0;
		u = strtoul(*s, &p, 10);
		*s = p;
		if(errno == ERANGE || u > 255)
			break;
		ret[i] = u;
		if(i == 3)
			return ret;
		if(*p != '.')
			break;
		(*s)++;
	}
	free(ret);
	return NULL;
}

static char * _gethostent_host(char const ** s)
{
	char * ret = NULL;
	size_t len = 0;
	char * p;

	for(; isalnum((int)(unsigned char)**s) || **s == '-' || **s == '.';
			(*s)++)
	{
		if((p = realloc(ret, len + 2)) == NULL)
			break;
		ret = p;
		p[len++] = **s;
	}
	if(len == 0)
		return NULL;
	ret[len] = '\0';
	return ret;
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
	if(_fp == NULL && (_fp = fopen("/etc/hosts", "r")) == NULL)
	{
		h_errno = NO_DATA;
		return;
	}
	fseek(_fp, 0, SEEK_SET);
}


/* private */
/* functions */
/* hostent_free */
static void _hostent_free(struct hostent * he)
{
	char ** p;

	free(he->h_name);
	for(p = he->h_aliases; p != NULL && *p != NULL; p++)
		free(*p);
	free(he->h_aliases);
	for(p = he->h_addr_list; p != NULL && *p != NULL; p++)
		free(*p);
	free(he->h_addr_list);
	memset(he, 0, sizeof(*he));
}
