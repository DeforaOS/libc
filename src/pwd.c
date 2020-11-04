/* $Id$ */
/* Copyright (c) 2005-2013 Pierre Pronchery <khorben@defora.org> */
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
#include "pwd.h"


/* private */
/* variables */
static FILE * _fp = NULL;


/* prototypes */
static int _getpwent_r(struct passwd * pw, char * buffer, size_t bufsize,
		struct passwd ** result);


/* public */
/* functions */
/* endpwent */
void endpwent(void)
{
	if(_fp == NULL)
		return;
	fclose(_fp);
	_fp = NULL;
}


/* getpwent */
struct passwd * getpwent(void)
{
	struct passwd * ret;
	static struct passwd pw;
	static char buf[512];

	_getpwent_r(&pw, buf, sizeof(buf), &ret);
	return ret;
}


/* getpwnam */
struct passwd * getpwnam(char const * name)
{
	struct passwd * pw;

	setpwent();
	while((pw = getpwent()) != NULL)
		if(strcmp(pw->pw_name, name) == 0)
			break;
	endpwent();
	return pw;
}


/* getpwnam_r */
int getpwnam_r(char const * name, struct passwd * pw, char * buffer,
		size_t bufsize, struct passwd ** result)
{
	int ret;

	setpwent();
	while((ret = _getpwent_r(pw, buffer, bufsize, result)) == 0
			&& result != NULL)
		if(strcmp(pw->pw_name, name) == 0)
			break;
	endpwent();
	return ret;
}


/* getpwuid */
struct passwd * getpwuid(uid_t uid)
{
	struct passwd * pw;

	setpwent();
	while((pw = getpwent()) != NULL)
		if(pw->pw_uid == uid)
			break;
	endpwent();
	return pw;
}


/* setpwent */
void setpwent(void)
{
	if(_fp == NULL)
		return;
	rewind(_fp);
}


/* private */
/* getpwent_r */
static int _getpwent_r_parse(struct passwd * pw, char * buffer, size_t bufsize,
		struct passwd ** result);

static int _getpwent_r(struct passwd * pw, char * buffer, size_t bufsize,
		struct passwd ** result)
{
	int c;

	*result = NULL;
	if(_fp == NULL && (_fp = fopen("/etc/passwd", "r")) == NULL)
		return -1;
	do
	{
		if(fgets(buffer, bufsize, _fp) == NULL)
		{
			endpwent();
			return -1;
		}
		if(strchr(buffer, '\n') == NULL)
			/* flush incomplete lines */
			while((c = fgetc(_fp)) != EOF && c != '\n');
	}
	while(buffer[0] == '#');
	return _getpwent_r_parse(pw, buffer, bufsize, result);
}

static int _getpwent_r_parse(struct passwd * pw, char * buffer, size_t bufsize,
		struct passwd ** result)
{
	char * s;
	char * t;

	s = buffer;
	/* check that the record is complete */
	if(strchr(s, '\n') == NULL)
	{
		errno = ERANGE;
		return -1;
	}
	/* read the user's name */
	if((t = strchr(s, ':')) == NULL)
		return -1;
	*t = '\0';
	pw->pw_name = s;
	/* read the user's password */
	s = ++t;
	if((t = strchr(s, ':')) == NULL)
		return -1;
	*t = '\0';
	pw->pw_gecos = s;
	/* read the user's id */
	s = ++t;
	if((t = strchr(s, ':')) == NULL)
		return -1;
	pw->pw_uid = atoi(s);
	/* read the user's group id */
	s = ++t;
	if((t = strchr(s, ':')) == NULL)
		return -1;
	pw->pw_gid = atoi(s);
	/* skip the user's description */
	s = ++t;
	if((t = strchr(s, ':')) == NULL)
		return -1;
	/* read the user's home directory */
	s = ++t;
	if((t = strchr(s, ':')) == NULL)
		return -1;
	*t = '\0';
	pw->pw_dir = s;
	pw->pw_shell = ++t;
	if((t = strchr(t, '\n')) == NULL)
		return -1;
	*t = '\0';
	*result = pw;
	return 0;
}
