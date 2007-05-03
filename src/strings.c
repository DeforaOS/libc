/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



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
