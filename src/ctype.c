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



#include "ctype.h"


/* functions */
/* isascii */
int isascii(int c)
{
	return c >= 0 && c <= 127;
}


/* isblank */
int isblank(int c)
{
	return c == ' ' || c == '\t';
}


/* iscntrl */
int iscntrl(int c)
{
	/* FIXME implement */
	return 0;
}


/* isdigit */
int isdigit(int c)
{
	return c >= '0' && c <= '9';
}


/* isgraph */
int isgraph(int c)
{
	return c > ' ' && c <= '~';
}


/* islower */
int islower(int c)
{
	return c >= 'a' && c <= 'z';
}


/* isprint */
int isprint(int c)
{
	return c >= ' ' && c <= '~';
}


/* isspace */
int isspace(int c)
{
	return c == ' ' || (c >= '\t' && c <= '\r');
}


/* isupper */
int isupper(int c)
{
	return c >= 'A' && c <= 'Z';
}


/* isxdigit */
int isxdigit(int c)
{
	return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f')
		|| (c >= 'A' && c <= 'F');
}


/* tolower */
int tolower(int c)
{
	if(isupper(c))
		return c + 'a' - 'A';
	return c;
}


/* toupper */
int toupper(int c)
{
	if(islower(c))
		return c + 'A' - 'a';
	return c;
}
