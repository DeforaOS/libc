/* $Id$ */
/* Copyright (c) 2004-2017 Pierre Pronchery <khorben@defora.org> */
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



#include "ctype.h"
#undef isalnum
#undef isalpha
#undef ispunct


/* functions */
/* isalnum */
int isalnum(int c)
{
	return isalpha(c) || isdigit(c);
}


/* isalpha */
int isalpha(int c)
{
	return islower(c) || isupper(c);
}


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


/* ispunct */
int ispunct(int c)
{
	return isprint(c) && (!(isspace(c) || isalnum(c)));
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


/* toascii */
int toascii(int c)
{
	return c & 0x7f;
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
