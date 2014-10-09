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
struct utmpx * getutxid(struct utmpx const * id)
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
		if((ret.ut_type == BOOT_TIME || ret.ut_type == OLD_TIME
					|| ret.ut_type == NEW_TIME)
				&& ret.ut_type == id->ut_type)
			break;
		if((ret.ut_type == INIT_PROCESS || ret.ut_type == LOGIN_PROCESS
					|| ret.ut_type == USER_PROCESS
					|| ret.ut_type == DEAD_PROCESS)
				&& (id->ut_type == INIT_PROCESS
					|| id->ut_type == LOGIN_PROCESS
					|| id->ut_type == OLD_TIME
					|| id->ut_type == NEW_TIME)
				&& ret.ut_id == id->ut_id)
			break;
	}
	return &ret;
}


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
