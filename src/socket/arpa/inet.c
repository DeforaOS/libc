/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
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
