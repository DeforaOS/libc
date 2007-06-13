/* $Id$ */
/* Copyright (c) 2007 Pierre Pronchery <khorben@defora.org> */
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



#include "ctype.h"
#include "strings.h"


/* ffs */
int ffs(int i)
{
	size_t bits = sizeof(i) * 8;
	size_t j;

	for(j = 0; j < bits; j++)
		if((i << (bits - j)) != 0)
			return j;
	return 0;
}


/* strcasecmp */
int strcasecmp(char const * s1, char const * s2)
{
	unsigned char const * u1;
	unsigned char const * u2;

	u1 = (unsigned char const *)s1;
	u2 = (unsigned char const *)s2;
	while(*u1 && *u2 && tolower(*u1) == tolower(*u2))
	{
		u1++;
		u2++;
	}
	return *u1 - *u2;
}


/* strncasecmp */
int strncasecmp(char const * s1, char const * s2, size_t n)
{
	unsigned char const * u1;
	unsigned char const * u2;

	u1 = (unsigned char const *)s1;
	u2 = (unsigned char const *)s2;
	while(--n && *u1 && *u2 && tolower(*u1) == tolower(*u2))
	{
		u1++;
		u2++;
	}
	return *u1 - *u2;
}
