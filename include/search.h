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
