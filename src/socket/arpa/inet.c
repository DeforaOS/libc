/* $Id$ */
/* Copyright (c) 2008 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* libc is not free software; you can redistribute it and/or modify it under
 * the terms of the Creative Commons Attribution-NonCommercial-ShareAlike 3.0
 * Unported as published by the Creative Commons organization.
 *
 * libc is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the Creative Commons Attribution-NonCommercial-
 * ShareAlike 3.0 Unported license for more details.
 *
 * You should have received a copy of the Creative Commons Attribution-
 * NonCommercial-ShareAlike 3.0 along with libc; if not, browse to
 * http://creativecommons.org/licenses/by-nc-sa/3.0/ */
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
