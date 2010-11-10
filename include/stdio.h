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

/* Maximum size of character array to hold ctermid() output */
# define L_ctermid	256


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
int getchar(void);
int pclose(FILE * stream);
void perror(char const * str);
FILE * popen(char const * command, char const * mode);
int printf(char const * format, ...);
int putc(int c, FILE * file);
int putchar(int c);
int puts(char const * string);
int remove(char const * path);
int rename(char const * from, char const * to);
void rewind(FILE * file);
int scanf(char const * format, ...);
void setbuf(FILE * file, char * buf);
int setvbuf(FILE * file, char * buf, int type, size_t size);
int snprintf(char * str, size_t size, char const * format, ...);
int sprintf(char * str, char const * format, ...);
int sscanf(char const * string, char const * format, ...);
FILE * tmpfile(void);
int ungetc(int c, FILE * file);
int vfprintf(FILE * file, char const * format, va_list arg);
int vfscanf(FILE * file, char const * format, va_list arg);
int vprintf(char const * format, va_list arg);
int vsnprintf(char * str, size_t size, char const * format, va_list arg);
int vsprintf(char * str, char const * format, va_list arg);

#endif /* !LIBC_STDIO_H */
