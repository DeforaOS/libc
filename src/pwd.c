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



#include "stddef.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "pwd.h"


/* private */
/* variables */
static FILE * _fp = NULL;


/* public */
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
	static struct passwd ret;
	static char buf[512];
	char * s;
	char * t;

	if(_fp == NULL && (_fp = fopen("/etc/passwd", "r")) == NULL)
		return NULL;
	if(fgets(buf, sizeof(buf), _fp) == NULL)
	{
		endpwent();
		return NULL;
	}
	s = buf; /* read the user's name */
	if((t = strchr(s, ':')) == NULL)
		return NULL;
	*t = '\0';
	ret.pw_name = s;
	s = ++t; /* skip the user's password */
	if((t = strchr(s, ':')) == NULL)
		return NULL;
	s = ++t; /* read the user's id */
	if((t = strchr(s, ':')) == NULL)
		return NULL;
	ret.pw_uid = atoi(s);
	s = ++t; /* read the user's group id */
	if((t = strchr(s, ':')) == NULL)
		return NULL;
	ret.pw_gid = atoi(s);
	s = ++t; /* skip the user's description */
	if((t = strchr(s, ':')) == NULL)
		return NULL;
	s = ++t; /* read the user's home directory */
	if((t = strchr(s, ':')) == NULL)
		return NULL;
	*t = '\0';
	ret.pw_dir = s;
	ret.pw_shell = ++t;
	return &ret;
}


/* getpwnam */
struct passwd * getpwnam(char const * name)
{
	struct passwd * pw;

	while((pw = getpwent()) != NULL)
		if(strcmp(pw->pw_name, name) == 0)
			break;
	endpwent();
	return pw;
}


/* getpwuid */
struct passwd * getpwuid(uid_t uid)
{
	struct passwd * pw;

	while((pw = getpwent()) != NULL)
		if(pw->pw_uid == uid)
			break;
	endpwent();
	return pw;
}


/* setpwent */
void setpwent(void)
{
	/* FIXME implement */
}
