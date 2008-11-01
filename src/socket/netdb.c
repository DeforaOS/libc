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



#include "sys/types.h"
#include "stdlib.h"
#include "errno.h"
#include "netdb.h"


/* functions */
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
	/* FIXME implement */
	errno = ENOSYS;
	return NULL;
}


/* getservbyname */
struct servent * getservbyname(const char * name, const char * protocol)
{
	/* FIXME implement */
	errno = ENOSYS;
	return NULL;
}
