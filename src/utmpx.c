/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#include "stdio.h"
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


/* getutxline */
/* FIXME implement */


/* pututxline */
/* FIXME implement */


/* setutxent */
/* FIXME implement */
