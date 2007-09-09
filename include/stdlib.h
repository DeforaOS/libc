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



#ifndef LIBC_STDLIB_H
# define LIBC_STDLIB_H

# include "stddef.h"


/* constants */
# define RAND_MAX 32767


/* functions */
int atoi(char const * str);
long atol(char const * str);
long long atoll(char const * nptr);
void * calloc(size_t nmemb, size_t size);
void exit(int status);
void free(void * ptr);
char * getenv(char const * name);
void * malloc(size_t size);
char * mktemp(char * template);
int mkstemp(char * template);
int rand(void);
void * realloc(void * ptr, size_t size);
int setenv(char const * name, char const * value, int overwrite);
void srand(unsigned seed);
long strtol(char const * str, char ** endptr, int base);
unsigned long strtoul(char const * str, char ** endptr, int base);
int unsetenv(char const * name);

#endif /* !LIBC_STDLIB_H */
