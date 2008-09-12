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



#include "stdlib.h"
#include "errno.h"
#include "search.h"


/* functions */
/* hcreate */
int hcreate(size_t nel)
{
	/* FIXME implement */
	errno = ENOSYS;
	return 0;
}


/* hdestroy */
void hdestroy(void)
{
	/* FIXME implement */
}


/* hsearch */
ENTRY * hsearch(ENTRY item, ACTION action)
{
	/* FIXME implement */
	errno = ENOSYS;
	return NULL;
}


/* insque */
void insque(void * elem, void * pred)
{
	/* FIXME implement */
}


/* lfind */
void * lfind(const void * key, const void * base, size_t * nelp,
		size_t width, int (*compar)(const void *, const void *))
{
	/* FIXME implement */
	return NULL;
}


/* lsearch */
void * lsearch(const void * key, void * base, size_t * nelp,
		size_t width, int (*compar)(const void *, const void *))
{
	/* FIXME implement */
	return NULL;
}


/* remque */
void remque(void * elem)
{
	/* FIXME implement */
}


/* tdelete */
void * tdelete(const void * key, void ** rootp,
		int (*compar)(const void *, const void *))
{
	if(rootp == NULL)
		return NULL;
	/* FIXME implement */
	errno = ENOSYS;
	return NULL;
}


/* tfind */
void * tfind(const void * key, void * const * rootp,
		int (*compar)(const void *, const void *))
{
	if(rootp == NULL)
		return NULL;
	/* FIXME implement */
	errno = ENOSYS;
	return NULL;
}


/* twalk */
void * tsearch(const void * key, void ** rootp,
		int (*compar)(const void *, const void *))
{
	if(rootp == NULL)
		return NULL;
	/* FIXME implement */
	errno = ENOSYS;
	return NULL;
}


/* twalk */
void twalk(const void * root, void (*action)(const void *, VISIT, int))
{
	/* FIXME implement */
}
