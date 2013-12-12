/* $Id$ */
/* Copyright (c) 2005-2013 Pierre Pronchery <khorben@defora.org> */
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
static int _getpwent_r(struct passwd * pw, char * buffer, size_t bufsize,
		struct passwd ** result)
{
	char * s;
	char * t;

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
	}
	while(buffer[0] == '#');
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
