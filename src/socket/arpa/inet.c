/* $Id$ */
/* Copyright (c) 2008-2015 Pierre Pronchery <khorben@defora.org> */
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
static const char * _ptest = (char*)&_test;


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
	in_addr_t ret = 0;
	unsigned long byte;
	char * p;
	int i;

	if(cp == NULL || cp[0] == '\0')
		return -1;
	for(i = 0; i < 4; i++)
	{
		byte = strtoul(cp, &p, 0);
		if(*p != '.' && *p != '\0')
			return -1;
		if(byte > 0xff)
			return -1;
		ret = (ret << 8) | byte;
		if(*p == '\0')
			return ret;
		cp = ++p;
	}
	return ret;
}


/* inet_aton */
int inet_aton(const char *cp, struct in_addr *addr)
{
	/* FIXME implement */
	return 0;
}


/* inet_ntoa */
char * inet_ntoa(struct in_addr in)
{
	static char ret[16];
	unsigned char * b = (unsigned char*)&in.s_addr;
	unsigned int i;
	unsigned int pos = 0;

	ret[0] = '\0';
	for(i = 0; pos <= sizeof(ret) && i < sizeof(in.s_addr); i++)
		pos += snprintf(&ret[pos], sizeof(ret) - pos, "%s%u",
				i ? "." : "", b[i]);
	return ret;
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
