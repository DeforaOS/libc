/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
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



#include "stddef.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "errno.h"
#include "grp.h"


/* private */
/* variables */
static FILE * _fp = NULL;


/* public */
/* functions */
/* endgrent */
void endgrent(void)
{
	if(_fp == NULL)
		return;
	fclose(_fp);
	_fp = NULL;
}


/* getgrent */
struct group * getgrent(void)
{
	static struct group ret;
	static char buf[512];
	char * s;
	char * t;

	if(_fp == NULL && (_fp = fopen("/etc/group", "r")) == NULL)
		return NULL;
	if(fgets(buf, sizeof(buf), _fp) == NULL)
	{
		endgrent();
		return NULL;
	}
	s = buf; /* read the group's name */
	if((t = strchr(s, ':')) == NULL)
		return NULL;
	*t = '\0';
	ret.gr_name = s;
	s = ++t; /* skip the group's password */
	if((t = strchr(s, ':')) == NULL)
		return NULL;
	s = ++t; /* read the group's id */
	if((t = strchr(s, ':')) == NULL)
		return NULL;
	ret.gr_gid = atoi(s);
	ret.gr_mem = NULL; /* FIXME implement */
	return &ret;
}


/* getgrgid */
struct group * getgrgid(gid_t gid)
{
	struct group * grp;

	while((grp = getgrent()) != NULL)
		if(grp->gr_gid == gid)
			break;
	endgrent();
	return grp;
}


/* getgrnam */
struct group * getgrnam(char const * name)
{
	struct group * grp;

	while((grp = getgrent()) != NULL)
		if(strcmp(grp->gr_name, name) == 0)
			break;
	endgrent();
	return grp;
}


/* setgrent */
void setgrent(void)
{
	/* FIXME implement */
}
