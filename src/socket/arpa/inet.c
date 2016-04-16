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
/* FIXME check if correct then optimize with macros or whatever */



#include "stdlib.h"
#include "stdio.h"
#include "sys/types.h"
#include "arpa/inet.h"


/* variables */
static const int _test = 0x1234;
static const char * _ptest = (char *)&_test;


/* functions */
/* htonl */
uint32_t htonl(uint32_t host32)
{
	if(*_ptest == 0x12)
		return host32;
	return ((host32 & 0xff) << 24) | ((host32 & 0xff00) << 8)
		| ((host32 & 0xff0000) >> 8) | ((host32 & 0xff000000) >> 24);
}


/* htons */
uint16_t htons(uint16_t host16)
{
	if(*_ptest == 0x12)
		return host16;
	return ((host16 & 0xff) << 8) | ((host16 & 0xff00) >> 8);
}


/* inet_addr */
in_addr_t inet_addr(const char *cp)
{
	struct in_addr ia;

	if(inet_aton(cp, &ia) != 1)
		return INADDR_NONE;
	return ia.s_addr;
}


/* inet_aton */
int inet_aton(const char *cp, struct in_addr *addr)
{
	unsigned long byte;
	char * p;
	int i;

	if(cp == NULL || cp[0] == '\0')
		return 0;
	addr->s_addr = 0;
	for(i = 0; i < 4; i++)
	{
		byte = strtoul(cp, &p, 0);
		if(*p != '.' && *p != '\0')
			return 0;
		if(byte > 0xff)
			return 0;
		addr->s_addr = (addr->s_addr << 8) | byte;
		if(*p == '\0')
		{
			addr->s_addr = htonl(addr->s_addr);
			return 1;
		}
		cp = ++p;
	}
	return 0;
}


/* inet_ntoa */
char * inet_ntoa(struct in_addr in)
{
	static char ret[16];

	if(inet_ntop(AF_INET, &in, ret, sizeof(ret)) == NULL)
		return NULL;
	return ret;
}


/* inet_ntop */
static char const * _ntop_inet(const struct in_addr * in, char * dst,
		socklen_t size);

char const * inet_ntop(int family, const void * src, char * dst, socklen_t size)
{
	const struct in_addr * in = src;

	switch(family)
	{
		case AF_INET:
			return _ntop_inet(in, dst, size);
		default:
			return NULL;
	}
}

static char const * _ntop_inet(const struct in_addr * in, char * dst,
		socklen_t size)
{
	unsigned char const * b = (unsigned char const *)&in->s_addr;
	unsigned int i;
	unsigned int pos;
	unsigned int p;

	for(i = 0, pos = 0;; i++)
		if(i == sizeof(in->s_addr))
			break;
		else if(i > sizeof(in->s_addr))
			return NULL;
		else if((p = snprintf(&dst[pos], size - pos, "%s%u",
						(i > 0) ? "." : "", b[i]))
				>= size - pos)
			return NULL;
		else
			pos += p;
	return dst;
}


/* ntohl */
uint32_t ntohl(uint32_t net32)
{
	return htonl(net32);
}


/* ntohs */
uint16_t ntohs(uint16_t net16)
{
	return htons(net16);
}
