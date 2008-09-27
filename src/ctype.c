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


/* isdigit */
int isdigit(int c)
{
	return c >= '0' && c <= '9';
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
