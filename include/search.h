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
