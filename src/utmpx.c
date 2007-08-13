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



#include "stdio.h"
#include "string.h"
#include "utmpx.h"


/* private */
static FILE * _fp = NULL;


/* public */
/* endutxent */
void endutxent(void)
{
	if(_fp == NULL)
		return;
	fclose(_fp);
	_fp = NULL;
}


/* getutxent */
struct utmpx * getutxent(void)
{
	static struct utmpx ret;

	if(_fp == NULL
			&& (_fp = fopen("/var/run/utmpx", "r")) == NULL
			&& (_fp = fopen("/var/run/utmp", "r")) == NULL)
		return NULL;
	if(fread(&ret, sizeof(ret), 1, _fp) != 1)
	{
		fclose(_fp);
		_fp = NULL;
		return NULL;
	}
	return &ret;
}


/* getutxid */
/* FIXME implement */


/* getutxline */
struct utmpx * getutxline(struct utmpx const * line)
{
	static struct utmpx ret;

	if(_fp == NULL
			&& (_fp = fopen("/var/run/utmpx", "r")) == NULL
			&& (_fp = fopen("/var/run/utmp", "r")) == NULL)
		return NULL;
	for(;;)
	{
		if(fread(&ret, sizeof(ret), 1, _fp) != 1)
		{
			fclose(_fp);
			_fp = NULL;
			return NULL;
		}
		if(ret.ut_type != LOGIN_PROCESS && ret.ut_type != USER_PROCESS)
			continue;
		if(strcmp(ret.ut_line, line->ut_line) == 0)
			break;
	}
	return &ret;
}


/* pututxline */
/* FIXME implement */


/* setutxent */
/* FIXME implement */
