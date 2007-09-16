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



#include "fnmatch.h"


/* fnmatch */
static int _fnmatch_class(char const * pattern, char const * str, int flags);

int fnmatch(char const * pattern, char const * string, int flags)
{
	int ret = 0;
	int i;

	if(flags & (FNM_PATHNAME | FNM_PERIOD | FNM_NOESCAPE))
		return FNM_NOSYS; /* FIXME implement */
	if(pattern[0] == '\0')
		return string[0] == '\0';
	if(pattern[0] == '*')
	{
		for(i = 0; string[i] != '\0'; i++)
			ret |= fnmatch(&pattern[1], &string[i], flags);
		return ret | fnmatch(&pattern[1], &string[i], flags);
	}
	if(*string == '\0')
		return 0;
	if(pattern[0] == '[')
		return _fnmatch_class(&pattern[1], string, flags);
	if(pattern[0] == string[0])
		return fnmatch(&pattern[1], &string[1], flags);
	return 0;
}

static int _fnmatch_class(char const * pattern, char const * str, int flags)
{
	int ret = 0;
	int neg = 0;
	unsigned int i;

	if(pattern[0] == '!')
	{
		neg = 1;
		pattern++;
	}
	if(*pattern == ']')
	{
		if(pattern[1] == '-' && pattern[2] != ']')
		{
			if (*str >= pattern[0] && *str <= pattern[2])
				ret = 1;
			pattern++;
		}
		else if (str[0] == ']')
			ret = FNM_NOMATCH;
		pattern++;
	}
	for(i = 0; pattern[i] != ']'; i++)
	{
		if(pattern[1] == '-' && pattern[i + 1] != ']')
		{
			if(*str >= pattern[i - 1] && str[0] <= pattern[i + 1])
				ret = FNM_NOMATCH;
			i++;
		}
		else if(pattern[i] == *str)
			ret = FNM_NOMATCH;
	}
	return ((str[0] != '\0' ? fnmatch(&pattern[i + 1], &str[1], flags) : 1)
		&& neg ^ ret) ? FNM_NOMATCH : 0;
}
