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



#ifndef LIBC_STRING_H
# define LIBC_STRING_H

# include "stddef.h"


/* functions */
void * memchr(void const * s, int c, size_t n);
int memcmp(void const * s1, void const * s2, size_t n);
void * memcpy(void * dest, void const * src, size_t n);
void * memmove(void * dest, void const * src, size_t n);
void * memset(void * dest, int c, size_t n);
char * strcat(char * dest, char const * src);
char * strchr(char const * s, int c);
int strcmp(char const * s1, char const * s2);
char * strcpy(char * dest, char const * src);
size_t strcspn(char const * s1, char const * s2);
char * strdup(char const * s);
char * strerror(int errnum);
int strerror_r(int errnum, char * strerrbuf, size_t buflen);
size_t strlen(char const * s);
char * strncat(char * dest, char const * src, size_t n);
int strncmp(char const * s1, char const * s2, size_t n);
char * strncpy(char * dest, char const * src, size_t n);
char * strpbrk(char const * s1, char const * s2);
char * strrchr(char const * s, int c);
size_t strspn(char const * s1, char const * s2);
char * strstr(char const * s1, char const * s2);
char * strtok(char * s1, char const * s2);

#endif /* !LIBC_STRING_H */
