/* $Id$ */
/* Copyright (c) 2007-2012 Pierre Pronchery <khorben@defora.org> */
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
