/* $Id$ */
/* Copyright (c) 2011 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_STDLIB_H
# define LIBC_STDLIB_H

# include "stddef.h"


/* constants */
# define EXIT_FAILURE	1
# define EXIT_SUCCESS	0

# define MB_CUR_MAX	1

# define RAND_MAX	32767


/* functions */
void abort(void);
int abs(int x);
int atexit(void (*function)(void));
double atof(char const * str);
int atoi(char const * str);
long atol(char const * str);
long long atoll(char const * nptr);
void * bsearch(const void * key, const void * base, size_t nel,
		size_t width, int (*compar)(const void *, const void *));
void * calloc(size_t nmemb, size_t size);
void exit(int status);
void free(void * ptr);
char * getenv(char const * name);
int getloadavg(double loadavg[], int nelem);
int grantpt(int fildes);
long labs(long x);
long long llabs(long long x);
void * malloc(size_t size);
char * mktemp(char * template);
int mkstemp(char * template);
char * ptsname(int fildes);
int putenv(char * str);
void qsort(void * base, size_t nel, size_t size,
		int (*compar)(const void *, const void *));
int rand(void);
void * realloc(void * ptr, size_t size);
int setenv(char const * name, char const * value, int overwrite);
void srand(unsigned seed);
double strtod(char const * str, char ** endptr);
float strtof(char const * str, char ** endptr);
long strtol(char const * str, char ** endptr, int base);
long double strtold(char const * str, char ** endptr);
long long strtoll(char const * str, char ** endptr, int base);
unsigned long strtoul(char const * str, char ** endptr, int base);
unsigned long long strtoull(char const * str, char ** endptr, int base);
int system(char const * command);
int unlockpt(int fildes);
int unsetenv(char const * name);

#endif /* !LIBC_STDLIB_H */
