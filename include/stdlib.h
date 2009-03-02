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
void qsort(void * base, size_t nel, size_t width,
		int (*compar)(const void *, const void *));
int rand(void);
void * realloc(void * ptr, size_t size);
int setenv(char const * name, char const * value, int overwrite);
void srand(unsigned seed);
double strtod(char const * str, char ** endptr);
float strtof(char const * str, char ** endptr);
long strtol(char const * str, char ** endptr, int base);
long long strtoll(char const * str, char ** endptr, int base);
unsigned long strtoul(char const * str, char ** endptr, int base);
unsigned long long strtoull(char const * str, char ** endptr, int base);
int system(char const * command);
int unlockpt(int fildes);
int unsetenv(char const * name);

#endif /* !LIBC_STDLIB_H */
