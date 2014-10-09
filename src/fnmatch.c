/* $Id$ */
/* Copyright (c) 2007-2013 Pierre Pronchery <khorben@defora.org> */
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



#include "fnmatch.h"


/* functions */
/* fnmatch */
static int _fnmatch_class(char const * pattern, char const * string, int flags);

int fnmatch(char const * pattern, char const * string, int flags)
{
	if(flags & (FNM_PATHNAME | FNM_PERIOD | FNM_NOESCAPE))
		return FNM_NOSYS; /* FIXME implement */
	if(pattern[0] == '\0')
		return (string[0] == '\0') ? 0 : FNM_NOMATCH;
	if(pattern[0] == '*')
	{
		for(; string[0] != '\0'; string++)
			if(fnmatch(&pattern[1], string, flags) == 0)
				return 0;
		return fnmatch(&pattern[1], string, flags);
	}
	if(string[0] == '\0')
		return FNM_NOMATCH;
	if(pattern[0] == '[')
		return _fnmatch_class(&pattern[1], string, flags);
	if(pattern[0] == '?')
		return fnmatch(&pattern[1], &string[1], flags);
	if(pattern[0] == string[0])
		return fnmatch(&pattern[1], &string[1], flags);
	return FNM_NOMATCH;
}

static int _fnmatch_class(char const * pattern, char const * string, int flags)
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
			if (*string >= pattern[0] && *string <= pattern[2])
				ret = 1;
			pattern++;
		}
		else if (string[0] == ']')
			ret = FNM_NOMATCH;
		pattern++;
	}
	for(i = 0; pattern[i] != ']'; i++)
	{
		if(pattern[1] == '-' && pattern[i + 1] != ']')
		{
			if(*string >= pattern[i - 1]
					&& string[0] <= pattern[i + 1])
				ret = FNM_NOMATCH;
			i++;
		}
		else if(pattern[i] == *string)
			ret = FNM_NOMATCH;
	}
	return ((string[0] != '\0' ? fnmatch(&pattern[i + 1], &string[1], flags)
				: 1) && neg ^ ret) ? FNM_NOMATCH : 0;
}
