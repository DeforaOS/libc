/* $Id$ */
/* Copyright (c) 2004-2015 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_STDIO_H
# define LIBC_STDIO_H

# include "compat/stdio.h"
# include "stddef.h"


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


/* constants */
/* size of <stdio.h> buffers */
# define BUFSIZ 8192

# define _IOFBF	0
# define _IOLBF	1
# define _IONBF	2

/* end-of-file return value */
# define EOF (-1)

/* maximum size of character array to hold ctermid() output */
# define L_ctermid 256

/* maximum size of character array to hold tmpnam() output */
# define L_tmpnam 1024 /* XXX OS dependent */


/* variables */
/* standard input, output, and error streams */
extern FILE * stdin;
extern FILE * stdout;
extern FILE * stderr;


/* functions */
void clearerr(FILE * file);
char * ctermid(char * buf);
int fclose(FILE * file);
FILE * fdopen(int fildes, char const * mode);
int feof(FILE * file);
int ferror(FILE * file);
int fflush(FILE * file);
int fgetc(FILE * file);
char * fgets(char * str, int size, FILE * file);
int fileno(FILE * file);
void flockfile(FILE * file);
FILE * fopen(char const * path, char const * mode);
int fprintf(FILE * file, char const * format, ...);
int fputc(int c, FILE * file);
int fputs(char const * str, FILE * file);
size_t fread(void * ptr, size_t size, size_t nb, FILE * file);
FILE * freopen(char const * path, char const * mode, FILE * file);
int fscanf(FILE * file, char const * format, ...);
int fseek(FILE * file, long offset, int whence);
int fseeko(FILE * file, off_t offset, int whence);
long ftell(FILE * file);
int ftrylock(FILE * file);
void funlockfile(FILE * file);
size_t fwrite(void const * ptr, size_t size, size_t nb, FILE * file);
int getc(FILE * file);
int getc_unlocked(FILE * file);
int getchar(void);
int getchar_unlocked(void);
int pclose(FILE * stream);
void perror(char const * str);
FILE * popen(char const * command, char const * mode);
int printf(char const * format, ...);
int putc(int c, FILE * file);
int putc_unlocked(int c, FILE * file);
int putchar(int c);
int putchar_unlocked(int c);
int puts(char const * string);
int remove(char const * path);
int rename(char const * from, char const * to);
int renameat(int fromfd, char const * from, int tofd, char const * to);
void rewind(FILE * file);
int scanf(char const * format, ...);
void setbuf(FILE * file, char * buf);
int setvbuf(FILE * file, char * buf, int type, size_t size);
int snprintf(char * str, size_t size, char const * format, ...);
int sprintf(char * str, char const * format, ...);
int sscanf(char const * string, char const * format, ...);
FILE * tmpfile(void);
char * tmpnam(char * str);
int ungetc(int c, FILE * file);
int vfprintf(FILE * file, char const * format, va_list arg);
int vfscanf(FILE * file, char const * format, va_list arg);
int vprintf(char const * format, va_list arg);
int vsnprintf(char * str, size_t size, char const * format, va_list arg);
int vsprintf(char * str, char const * format, va_list arg);

#endif /* !LIBC_STDIO_H */
