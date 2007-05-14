/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#include "stddef.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "errno.h"
#include "grp.h"


/* private */
/* variables */
static FILE * _fp = NULL;


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
