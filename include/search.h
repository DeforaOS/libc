/* $Id$ */
/* Copyright (c) 2008 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_SEARCH_H
# define LIBC_SEARCH_H


/* types */
typedef enum { FIND, ENTER } ACTION;
typedef enum { preorder, postorder, endorder, leaf } VISIT;

typedef struct _ENTRY
{
	char * key;
	void * data;
} ENTRY;

# ifndef size_t
#  define size_t size_t
typedef unsigned long size_t;
# endif


/* functions */
int hcreate(size_t nel);
void hdestroy(void);
ENTRY * hsearch(ENTRY item, ACTION action);
void insque(void * elem, void * pred);
void * lfind(const void * key, const void * base, size_t * nelp,
		size_t width, int (*compar)(const void *, const void *));
void * lsearch(const void * key, void * base, size_t * nelp,
		size_t width, int (*compar)(const void *, const void *));
void remque(void * elem);
void * tdelete(const void * key, void ** rootp,
		int (*compar)(const void *, const void *));
void * tfind(const void * key, void * const * rootp,
		int (*compar)(const void *, const void *));
void * tsearch(const void * key, void ** rootp,
		int (*compar)(const void *, const void *));
void twalk(const void * root,
		void (*action)(const void *, VISIT, int));

#endif /* !LIBC_SEARCH_H */
