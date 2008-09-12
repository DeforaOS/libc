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



#ifndef LIBC_STDIO_H
# define LIBC_STDIO_H

# include "stddef.h"


/* constants */
/* size of <stdio.h> buffers */
# define BUFSIZ 8192

/* end-of-file return value */
# define EOF (-1)


/* types */
# ifndef FILE
#  define FILE FILE
typedef struct _FILE FILE;
# endif

# ifndef va_list
#  if defined(__i386__)
#   define va_list va_list
typedef void * va_list;
#  elif defined(__amd64__) \
	|| defined(__arm__) \
	|| defined(__mips__) \
	|| defined(__sparc__) \
	|| defined(__sparc64__)	/* XXX compiler dependent */
#   define va_list		__builtin_va_list
#  else
#   warning Unsupported architecture
#   define va_list va_list
typedef void * va_list;
#  endif
# endif


/* variables */
/* standard input, output, and error streams */
extern FILE * stdin;
extern FILE * stdout;
extern FILE * stderr;


/* functions */
void clearerr(FILE * file);
int fclose(FILE * file);
FILE * fdopen(int fildes, char const * mode);
int feof(FILE * file);
int ferror(FILE * file);
int fflush(FILE * file);
int fgetc(FILE * file);
char * fgets(char * str, int size, FILE * file);
int fileno(FILE * file);
FILE * fopen(char const * path, char const * mode);
int fprintf(FILE * file, char const * format, ...);
int fputc(int c, FILE * file);
int fputs(char const * str, FILE * file);
size_t fread(void * ptr, size_t size, size_t nb, FILE * file);
FILE * freopen(char const * path, char const * mode, FILE * file);
int fscanf(FILE * file, char const * format, ...);
int fseek(FILE * file, long offset, int whence);
size_t fwrite(void const * ptr, size_t size, size_t nb, FILE * file);
int getc(FILE * file);
int getchar(void);
void perror(char const * str);
int printf(char const * format, ...);
int putc(int c, FILE * file);
int putchar(int c);
int puts(char const * string);
int rename(char const * from, char const * to);
int snprintf(char * str, size_t size, char const * format, ...);
int sprintf(char * str, char const * format, ...);
FILE * tmpfile(void);
int vfprintf(FILE * file, char const * format, va_list arg);
int vsnprintf(char * str, size_t size, char const * format, va_list arg);
int vsprintf(char * str, char const * format, va_list arg);

#endif /* !LIBC_STDIO_H */
