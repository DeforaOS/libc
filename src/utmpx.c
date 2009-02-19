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
