/* $Id$ */
/* Copyright (c) 2007-2013 Pierre Pronchery <khorben@defora.org> */
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
