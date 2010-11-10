/* $Id$ */
/* Copyright (c) 2010 Pierre Pronchery <khorben@defora.org> */
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
