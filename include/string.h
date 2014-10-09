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
int strcoll(char const * s1, char const * s2);
char * strcpy(char * dest, char const * src);
size_t strcspn(char const * s1, char const * s2);
char * strdup(char const * s);
char * strerror(int errnum);
int strerror_r(int errnum, char * strerrbuf, size_t buflen);
size_t strlen(char const * s);
char * strncat(char * dest, char const * src, size_t n);
int strncmp(char const * s1, char const * s2, size_t n);
char * strncpy(char * dest, char const * src, size_t n);
size_t strnlen(char const * s, size_t max);
char * strpbrk(char const * s1, char const * s2);
char * strrchr(char const * s, int c);
size_t strspn(char const * s1, char const * s2);
char * strstr(char const * s1, char const * s2);
char * strtok(char * s1, char const * s2);
size_t strxfrm(char * s1, char const * s2, size_t n);

#endif /* !LIBC_STRING_H */
