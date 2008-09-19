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



#include "errno.h"
#include "fcntl.h"
#include "unistd.h"
#include "stdarg.h"
#include "stdlib.h"
#include "string.h"
#include "limits.h"
#include "syscalls.h"
#include "stdio.h"

#define min(a, b) ((a) > (b) ? (b) : (a))


/* types */
typedef enum _FILEBuffering
{
	FB_BUFFERED, FB_UNBUFFERED, FB_LINE
} FILEBuffering;
typedef enum _FILEDirection { FD_READ = 0, FD_WRITE = 1 } FILEDirection;

struct _FILE
{
	int fd;
	int flags;
	unsigned char buf[BUFSIZ];
	unsigned int len;
	unsigned int pos;
	char eof;
	char error;
	FILEBuffering fbuf;
	FILEDirection dir;
};


/* variables */
static FILE _stdin =
{
	STDIN_FILENO, O_RDONLY, { 0 }, 0, 0, 0, 0, FB_BUFFERED, FD_READ
};
FILE * stdin = &_stdin;

static FILE _stdout =
{
	STDOUT_FILENO, O_WRONLY, { 0 }, 0, 0, 0, 0, FB_LINE, FD_WRITE
};
FILE * stdout = &_stdout;

static FILE _stderr =
{
	STDERR_FILENO, O_WRONLY, { 0 }, 0, 0, 0, 0, FB_UNBUFFERED, FD_WRITE
};
FILE * stderr = &_stderr;


/* functions */
/* private */
/* PRE
 * POST
 * 	-1	error
 * 	else	corresponding mode */
static int _fopen_mode(char const * mode)
{
	int flags;

	if(*mode == 'r')
	{
		flags = O_RDONLY;
		if(*++mode == 'b')
			++mode;
		if(*mode == '\0')
			return flags;
		if(*mode == '+' && ++mode)
			flags = O_RDWR;
	}
	else if(*mode == 'w')
	{
		flags = O_WRONLY | O_CREAT;
		if(*++mode == 'b')
			++mode;
		if(*mode == '\0')
			return flags;
		if(*mode == '+' && ++mode)
			flags = O_RDWR | O_CREAT;
	}
	else if(*mode == 'a')
	{
		flags = O_APPEND;
		if(*++mode == 'b')
			++mode;
		if(*mode == '\0')
			return flags;
		if(*mode == '+' && ++mode)
			flags |= O_CREAT;
	}
	else
	{
		errno = EINVAL;
		return -1;
	}
	if(*mode == 'b')
		++mode;
	if(*mode != '\0')
	{
		errno = EINVAL;
		return -1;
	}
	return flags;
}


/* public */
/* clearerr */
void clearerr(FILE * file)
{
	file->eof = 0;
	file->error = 0;
}


/* fclose */
int fclose(FILE * file)
{
	int ret;
	
	ret = fflush(file);
	close(file->fd);
	return ret;
}


/* fdopen */
FILE * fdopen(int fd, char const * mode)
{
	FILE * file;

	if((file = malloc(sizeof(FILE))) == NULL)
		return NULL;
	if((file->flags = _fopen_mode(mode)) == -1)
	{
		free(file);
		return NULL;
	}
	file->fd = fd;
	file->len = 0;
	file->pos = 0;
	file->eof = 0;
	file->error = 0;
	file->dir = file->flags & O_WRONLY ? FD_WRITE : FD_READ;
	file->fbuf = isatty(file->fd) ? FB_UNBUFFERED : FB_BUFFERED;
	return file;
}


/* feof */
int feof(FILE * file)
{
	return file->eof;
}


/* ferror */
int ferror(FILE * file)
{
	return file->error;
}


/* fflush */
int fflush(FILE * file)
{
	ssize_t w;

	if(file == NULL)
	{
		errno = ENOSYS; /* FIXME implement */
		return -1;
	}
	if(file->dir == FD_READ)
	{
		file->len = 0;
		file->pos = 0;
		return 0;
	}
	else if(file->dir != FD_WRITE)
		return EOF;
	for(; file->pos < file->len; file->pos += w)
		if((w = write(file->fd, &file->buf[file->pos],
						file->len - file->pos)) < 0)
		{
			file->error = 1;
			return EOF;
		}
	file->pos = 0;
	file->len = 0;
	return 0;
}


/* fgetc */
int fgetc(FILE * file)
{
	char c;

	if(fread(&c, sizeof(char), 1, file) != 1)
		return EOF;
	return c;
}


/* fgets */
char * fgets(char * str, int size, FILE * fp)
{
	int i;
	int c;

	if(size < 0)
	{
		errno = EINVAL;
		return NULL;
	}
	for(i = 0; i + 1 < size; i++)
	{
		if((c = fgetc(fp)) == EOF)
		{
			if(i == 0 || !feof(fp))
				return NULL;
			break;
		}
		str[i] = c;
		if(c == '\n')
			break;
	}
	if(++i >= size)
		return NULL;
	str[i] = '\0';
	return str;
}


/* fileno */
int fileno(FILE * file)
{
	if(file == NULL)
	{
		errno = EBADF;
		return -1;
	}
	return file->fd;
}


/* fopen */
FILE * fopen(char const * path, char const * mode)
{
	FILE * file;

	if((file = malloc(sizeof(FILE))) == NULL)
		return NULL;
	if((file->flags = _fopen_mode(mode)) == -1
			|| (file->fd = open(path, file->flags, 0777)) < 0)
	{
		free(file);
		return NULL;
	}
	file->len = 0;
	file->pos = 0;
	file->eof = 0;
	file->error = 0;
	file->dir = file->flags & O_WRONLY ? FD_WRITE : FD_READ;
	file->fbuf = isatty(file->fd) ? FB_UNBUFFERED : FB_BUFFERED;
	return file;
}


/* fprintf */
int fprintf(FILE * file, char const * format, ...)
{
	int ret;
	va_list arg;

	va_start(arg, format);
	ret = vfprintf(file, format, arg);
	va_end(arg);
	return ret;
}


/* fputc */
int fputc(int c, FILE * file)
{
	unsigned char p = c;

	if(fwrite(&p, sizeof(char), 1, file) != 1)
		return EOF;
	return p;
}


/* fputs */
int fputs(char const * str, FILE * file)
{
	size_t len;

	if((len = strlen(str)) == 0)
		return 0;
	return fwrite(str, sizeof(char), len, file) == len ? 0 : EOF;
}


/* fread */
size_t fread(void * ptr, size_t size, size_t nb, FILE * file)
{
	char * p = (char*)ptr;
	size_t i;
	size_t j;
	size_t len;
	ssize_t r;

	if(file->dir != FD_READ)
	{
		if(fflush(file) != 0)
			return 0;
		else
			file->dir = FD_READ;
	}
	for(i = 0; i < nb; i++)
		for(j = 0; j < size; j += len)
		{
			if(file->pos == file->len)
			{
				if((r = read(file->fd, file->buf, BUFSIZ)) < 0)
				{
					file->error = 1;
					return i;
				}
				else if(r == 0)
				{
					file->eof = 1;
					return i;
				}
				file->pos = 0;
				file->len = r;
			}
			len = min(file->len - file->pos, size - j);
			memcpy(p, &file->buf[file->pos], len);
			file->pos += len;
			p += len;
		}
	return i;
}


/* freopen */
FILE * freopen(char const * path, char const * mode, FILE * file)
{
	int flags;

	fflush(file);
	if(path == NULL)
	{
		if((flags = _fopen_mode(mode)) == -1)
		{
			if(fcntl(file->fd, F_SETFL, flags) == -1)
				return NULL;
			file->flags = flags;
			file->dir = flags & O_WRONLY ? FD_WRITE : FD_READ;
			return file;
		}
	}
	close(file->fd);
	clearerr(file);
	if((flags = _fopen_mode(mode)) == -1
			|| (file->fd = open(path, file->flags, 0777)) < 0)
		return NULL;
	file->flags = flags;
	file->dir = flags & O_WRONLY ? FD_WRITE : FD_READ;
	file->fbuf = isatty(file->fd) ? FB_UNBUFFERED : FB_BUFFERED;
	return file;
}


/* fscanf */
int fscanf(FILE * fp, char const * format, ...)
{
	/* FIXME implement */
	errno = ENOSYS;
	return EOF;
}


/* fseek */
int fseek(FILE * file, long offset, int whence)
{
	if(fflush(file) != 0)
		return 1;
	return lseek(file->fd, offset, whence) != -1 ? 0 : -1;
}


/* fwrite */
size_t fwrite(void const * ptr, size_t size, size_t nb, FILE * file)
{
	char const * p = (char const *)ptr;
	size_t i;
	size_t j;
	size_t len;
	ssize_t w;

	if(file->dir != FD_WRITE)
	{
		if(fflush(file) != 0)
			return 0;
		file->dir = FD_WRITE;
	}
	for(i = 0; i < nb; i++)
		for(j = 0; j < size; j+=len)
		{
			len = min(BUFSIZ - file->len, size - j);
			memcpy(&file->buf[file->len], p, len);
			p += len;
			file->len += len;
			if(file->len != BUFSIZ) /* buffer is not full */
				continue;
			if((w = write(file->fd, &file->buf[file->pos], BUFSIZ
							- file->pos)) < 0)
			{
				file->error = 1;
				return i;
			}
			if(w != BUFSIZ - (ssize_t)file->pos) /* XXX cast */
				file->pos = w; /* buffer is not empty */
			else /* buffer is empty */
			{
				file->pos = 0;
				file->len = 0;
			}
		}
	if(file->fbuf == FB_BUFFERED)
		return nb;
	if(file->fbuf == FB_LINE)
	{
		j = file->pos;
		for(i = j; i < file->len; i++)
			if(file->buf[i] == '\n')
				j = i;
	}
	else /* file is unbuffered */
		j = file->len;
	for(; file->pos < j; file->pos += w) /* empty buffer if necessary */
		if((w = write(file->fd, &file->buf[file->pos], j - file->pos))
				< 0)
		{
			file->error = 1;
			break; /* XXX should we otherwise report the error? */
		}
	return nb;
}


/* getc */
int getc(FILE * file)
{
	return fgetc(file);
}


/* perror */
void perror(char const * s)
{
	if(s != NULL && *s != '\0')
		fprintf(stderr, "%s%s", s, ": ");
	fputs(strerror(errno), stderr);
	fputc('\n', stderr);
}


/* printf */
int printf(char const * format, ...)
{
	int ret;
	va_list arg;

	va_start(arg, format);
	ret = vfprintf(stdout, format, arg);
	va_end(arg);
	return ret;
}


/* putc */
int putc(int c, FILE * fp)
{
	return fputc(c, fp);
}


/* putchar */
int putchar(int c)
{
	return fputc(c, stdout);
}


/* puts */
int puts(char const * string)
{
	size_t i;
	
	i = strlen(string);
	if(fwrite(string, sizeof(char), i, stdout) != i)
		return EOF;
	fputc('\n', stdout);
	return i <= INT_MAX ? i : INT_MAX;
}


/* rename */
#ifndef SYS_rename
# warning Unsupported platform: rename() is missing
#endif


/* snprintf */
int snprintf(char * str, size_t size, char const * format, ...)
{
	va_list arg;
	int ret;

	va_start(arg, format);
	ret = vsnprintf(str, size, format, arg);
	va_end(arg);
	return ret;
}


/* sprintf */
int sprintf(char * str, char const * format, ...)
{
	va_list arg;
	int ret;

	va_start(arg, format);
	ret = vsprintf(str, format, arg);
	va_end(arg);
	return ret;
}


/* tmpfile */
FILE * tmpfile(void)
{
	char * path;
	int fd;
	FILE * fp;

	if((path = mktemp("/tmp/tmp.XXXXXX")) == NULL)
		return NULL;
	if((fd = open(path, O_WRONLY | O_CREAT | O_EXCL, 0666)) < 0)
		return NULL;
	if(unlink(path) != 0
			|| (fp = fdopen(fd, "w+")) == NULL)
	{
		close(fd);
		return NULL;
	}
	return fp;
}


/* ungetc */
int ungetc(int c, FILE * file)
{
	if(c == EOF || c < 0)
	{
		errno = EINVAL;
		return EOF;
	}
	if(file->len == sizeof(file->buf))
	{
		errno = ENOBUFS;
		return EOF;
	}
	memmove(&file->buf[file->pos + 1], &file->buf[file->pos], file->len
			- file->pos);
	file->buf[file->pos] = c; /* XXX c may be silently truncated */
	file->len++;
	return file->buf[file->pos];
}


/* vfprintf */
typedef int (*print_func)(void * dest, size_t size, const char * buf);
static int _fprint(void * dest, size_t size, const char * buf);
static int _vprintf(print_func func, void * dest, size_t size,
		char const * format, va_list arg);

int vfprintf(FILE * file, char const * format, va_list arg)
{
	return _vprintf(_fprint, file, ~0, format, arg);
}

static int _fprint(void * dest, size_t size, char const buf[])
{
	FILE * fp = dest;

	return fwrite(buf, sizeof(char), size, fp);
}

/* _vprintf */
#define FLAGS_HASH	0x01
#define FLAGS_MINUS	0x02
#define FLAGS_PLUS	0x04
#define FLAGS_SPACE	0x08
#define FLAGS_ZERO	0x10
static char _vprintf_flags(char const * p, size_t * i);
static size_t _vprintf_width(char const * p, size_t * i);
static size_t _vprintf_precision(char const * p, size_t * i);
static void _format_lutoa(char * dest, unsigned long n, size_t base);
static int _format_c(print_func func, void * dest, size_t size, size_t * len,
		char * chrp);
static int _format_d(print_func func, void * dest, size_t size, size_t * len,
		long long * ptr);
static int _format_o(print_func func, void * dest, size_t size, size_t * len,
		unsigned long long * ptr);
static int _format_s(print_func func, void * dest, size_t size, size_t * len,
		char * str);
static int _format_p(print_func func, void * dest, size_t size, size_t * len,
		void * ptr);
static int _format_u(print_func func, void * dest, size_t size, size_t * len,
		unsigned long long * ptr);
static int _format_x(print_func func, void * dest, size_t size, size_t * len,
		unsigned long long * ptr);

static int _vprintf(print_func func, void * dest, size_t size,
		char const * format, va_list arg)
{
	int ret = 0;
	char const * p;		/* pointer to current format character */
	size_t i;
	size_t len;		/* length to output at current iteration */
	char flags;
	size_t width;
	size_t precision;
	int lng;
	char c;
	char * str;
	long long int d;
	unsigned long long int u;
	void * ptr;

	for(p = format; *p != '\0'; p += i)
	{
		for(i = 0; p[i] != '\0' && p[i] != '%'; i++);
		if(i > 0)
		{
			len = min(i, size);
			if(func(dest, len, p) != len)
				return -1;
		}
		else if(*(p++) == '%')
		{
			len = 0;
			flags = _vprintf_flags(p, &i);
			width = _vprintf_width(p, &i);
			precision = _vprintf_precision(p, &i);
			for(lng = 0; p[i] != '\0'; i++)
			{
				if(p[i] == 'l')
				{
					if(++lng > 2)
					{
						errno = EINVAL;
						return -1;
					}
				}
				else if(p[i] == 'c')
				{
					c = va_arg(arg, int);
					if(_format_c(func, dest, size, &len, &c)
							== -1)
						return -1;
					break;
				}
				else if(p[i] == 'd')
				{
					if(lng > 1)
						d = va_arg(arg, long long int);
					else if (lng == 1)
						d = va_arg(arg, long int);
					else
						d = va_arg(arg, int);
					if(_format_d(func, dest, size, &len, &d)
							== -1)
						return -1;
					break;
				}
				else if(p[i] == 'o')
				{
					if(lng > 1)
						u = va_arg(arg, unsigned long
								long int);
					else if(lng == 1)
						u = va_arg(arg, unsigned long
									int);
					else
						u = va_arg(arg, unsigned int);
					if(_format_o(func, dest, size, &len, &u)
							== -1)
						return -1;
					break;
				}
				else if(p[i] == 'p')
				{
					ptr = va_arg(arg, void*);
					if(_format_p(func, dest, size, &len,
								ptr) == -1)
						return -1;
					break;
				}
				else if(p[i] == 's')
				{
					str = va_arg(arg, char*);
					if(_format_s(func, dest, size, &len,
								str) == -1)
						return -1;
					break;
				}
				else if(p[i] == 'u')
				{
					if(lng > 1)
						u = va_arg(arg, unsigned long
								long int);
					else if(lng == 1)
						u = va_arg(arg, unsigned long
									int);
					else
						u = va_arg(arg, unsigned int);
					if(_format_u(func, dest, size, &len, &u)
							== -1)
						return -1;
					break;
				}
				else if(p[i] == 'x')
				{
					if(lng > 1)
						u = va_arg(arg, unsigned long
								long int);
					else if(lng == 1)
						u = va_arg(arg, unsigned long
								int);
					else
						u = va_arg(arg,	unsigned int);
					if(_format_x(func, dest, size, &len, &u)
							== -1)
						return -1;
					break;
				}
				else if(p[i] == 'z')
				{
					if(lng != 0)
					{
						errno = EINVAL;
						return -1;
					}
					lng = 1;
				}
				else
				{
					errno = EINVAL;
					return -1;
				}
			}
			i++;
		}
		if(INT_MAX - len < ret)
		{
			errno = ERANGE;
			return -1;
		}
		size -= len;
		ret += len;
	}
	return ret;
}

static char _vprintf_flags(char const * p, size_t * i)
{
	char flags = 0;

	for(; p[*i] != '\0'; (*i)++)
	{
		if(p[*i] == '#')
			flags |= FLAGS_HASH;
		else if(p[*i] == '-')
			flags |= FLAGS_MINUS;
		else if(p[*i] == '+')
			flags |= FLAGS_PLUS;
		else if(p[*i] == ' ')
			flags |= FLAGS_SPACE;
		else if(p[*i] == '0')
			flags |= FLAGS_ZERO;
		else
			break;
	}
	return flags;
}

static size_t _vprintf_width(char const * p, size_t * i)
{
	size_t width = 0;

	for(; p[*i] != '\0'; (*i)++)
	{
		if(p[*i] < '0' || p[*i] > '9')
			break;
		width *= 10;
		width += p[*i] - '0';
	}
	return width;
}

static size_t _vprintf_precision(char const * p, size_t * i)
{
	if(p[*i] != '.')
		return 0;
	(*i)++;
	return _vprintf_width(p, i);
}

static int _format_c(print_func func, void * dest, size_t size, size_t * len,
		char * chrp)
{
	if(size == 0)
	{
		*len = 0;
		return 0;
	}
	if(func(dest, 1, chrp) != 1)
		return -1;
	*len = 1;
	return 0;
}

static int _format_d(print_func func, void * dest, size_t size, size_t * len,
		long long * ptr)
{
	unsigned long long uval;

	if(*ptr >= 0)
	{
		uval = *ptr;
		return _format_u(func, dest, size - 1, len, &uval);
	}
	uval = -(*ptr);
	if(func(dest, 1, "-") != 1
			|| _format_u(func, dest, size - 1, len, &uval) == -1)
		return -1;
	(*len)++;
	return 0;
}

static int _format_o(print_func func, void * dest, size_t size, size_t * len,
		unsigned long long * ptr)
{
	char tmp[22] = "";
	int l;

	_format_lutoa(tmp, *ptr, 8); /* XXX assumes tmp is large enough */
	*len = strlen(tmp);
	l = min(*len, size);
	if(func(dest, l, tmp) != l)
		return -1;
	return 0;
}

static int _format_s(print_func func, void * dest, size_t size, size_t * len,
		char * str)
{
	int l;

	*len = strlen(str);
	l = min(*len, size);
	if(func(dest, l, str) != l)
		return -1;
	return 0;
}

static int _format_p(print_func func, void * dest, size_t size, size_t * len,
		void * ptr)
{
	char tmp[3 + sizeof(void*) + sizeof(void*)] = "0x";
	int l;

	*len = sizeof(tmp);
	l = min(sizeof(tmp), size);
	_format_lutoa(&tmp[2], (long)ptr, 16); /* XXX cast */
	if(func(dest, l, tmp) != l)
		return -1;
	return 0;
}

static int _format_u(print_func func, void * dest, size_t size, size_t * len,
		unsigned long long * ptr)
{
	char tmp[19] = "";
	int l;

	_format_lutoa(tmp, *ptr, 10); /* XXX assumes tmp is large enough */
	*len = strlen(tmp);
	l = min(*len, size);
	if(func(dest, l, tmp) != l)
		return -1;
	return 0;
}

static int _format_x(print_func func, void * dest, size_t size, size_t * len,
		unsigned long long * ptr)
{
	char tmp[sizeof(long) + sizeof(long) + 1] = "";
	int l;

	_format_lutoa(tmp, *ptr, 16); /* XXX assumes tmp is large enough */
	*len = strlen(tmp);
	l = min(*len, size);
	if(func(dest, l, tmp) != l)
		return -1;
	return 0;
}

/* PRE	dest is long enough
 * POST	2 <= base <= 36		dest is the ascii representation of n
 *	else			dest is an empty string */
static void _format_lutoa(char * dest, unsigned long n, size_t base)
{
	static char const conv[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	size_t len = 0;
	unsigned long p;
	size_t i;

	if(base < 2 || base >= sizeof(conv))
	{
		dest[0] = '\0';
		return;
	}
	if(n == 0)
	{
		strcpy(dest, "0");
		return;
	}
	/* XXX performing twice the divisions is not optimal */
	for(p = n; p > 0; p /= base)
		len++;
	for(i = len; n > 0; n /= base)
	{
		p = n % base;
		dest[--i] = conv[p];
		n -= p;
	}
	dest[len] = '\0';
}


/* vsnprintf */
static int _sprint(void * dest, size_t size, const char * buf);

int vsnprintf(char * str, size_t size, char const * format, va_list arg)
{
	int ret;
	char * p = str;
	size_t i;

	if((ret = _vprintf(_sprint, &p, size, format, arg)) < 0)
		return ret;
	i = ret;
	if(i < size)
		str[ret] = '\0';
	else if(size > 0)
		str[size - 1] = '\0';
	return ret;
}

static int _sprint(void * dest, size_t size, char const buf[])
{
	char ** str = dest;

	strncpy(*str, buf, size);
	*str += size;
	return size;
}


/* vsprintf */
int vsprintf(char * str, char const * format, va_list arg)
{
	int ret;
	char * p = str;
	size_t size = -1;

	if((ret = _vprintf(_sprint, &p, size, format, arg)) < 0)
		return ret;
	str[ret] = '\0';
	return ret;
}
