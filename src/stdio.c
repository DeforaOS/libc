/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



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
struct _FILE
{
	int fildes;
	int flags;
	unsigned char buf[BUFSIZ];
	unsigned int len;
	unsigned int pos;
	char eof;
};


/* variables */
static FILE _stdin = { 0, O_RDONLY, { 0 }, 0, 0, 0 };
FILE * stdin = &_stdin;
static FILE _stdout = { 1, O_WRONLY, { 0 }, 0, 0, 0 };
FILE * stdout = &_stdout;
static FILE _stderr = { 2, O_WRONLY, { 0 }, 0, 0, 0 };
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
		if(*mode == 'b')
			++mode;
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
		if(*mode == 'b')
			++mode;
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
		if(*mode == 'b')
			++mode;
	}
	else
	{
		errno = EINVAL;
		return -1;
	}
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
}


/* fclose */
int fclose(FILE * file)
{
	int res;
	
	res = fflush(file);
	close(file->fildes);
	return res;
}


/* fdopen */
FILE * fdopen(int fildes, char const * mode)
{
	FILE * file;

	if((file = malloc(sizeof(FILE))) == NULL)
		return NULL;
	if((file->flags = _fopen_mode(mode)) == -1)
	{
		free(file);
		return NULL;
	}
	file->fildes = fildes;
	file->len = 0;
	file->pos = 0;
	file->eof = 0;
	return file;
}


/* feof */
int feof(FILE * file)
{
	return file->eof;
}


/* fflush */
int fflush(FILE * file)
{
	ssize_t count;

	if(file->flags & O_RDONLY)
	{
		file->len = 0;
		file->pos = 0;
		return 0;
	}
	else if(file->flags & O_RDWR)
	{
		errno = ENOSYS;
		return EOF;
	}
	for(; file->len > 0; file->len -= count)
		if((count = write(file->fildes, file->buf, count)) == -1)
			return EOF;
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


/* fileno */
int fileno(FILE * file)
{
	if(file == NULL)
	{
		errno = EBADF;
		return -1;
	}
	return file->fildes;
}


/* fopen */
FILE * fopen(char const * path, char const * mode)
{
	FILE * file;

	if((file = malloc(sizeof(FILE))) == NULL)
		return NULL;
	if((file->flags = _fopen_mode(mode)) == -1
			|| (file->fildes = open(path, file->flags)) < 0)
	{
		free(file);
		return NULL;
	}
	file->len = 0;
	file->pos = 0;
	file->eof = 0;
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
	ssize_t len;
	size_t cnt;

	if(size > BUFSIZ)
	{
		/* FIXME buffer can't handle this, call read repetedly */
		errno = ENOBUFS;
		return -1;
	}
	for(cnt = file->len / size; cnt < nb; cnt = file->len / size)
	{
		if((len = read(file->fildes, &file->buf[file->len],
				BUFSIZ - file->len)) == 0)
			break;
		if(len == -1)
			return -1;
		file->len += len;
	}
	cnt = min(nb, cnt);
	memcpy(ptr, file->buf, size * cnt);
	memmove(file->buf, &file->buf[size * cnt], file->len - (size * cnt));
	file->len -= size * cnt;
	return cnt;
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
			if(fcntl(file->fildes, F_SETFL, flags) == -1)
				return NULL;
			file->flags = flags;
			return file;
		}
	}
	close(file->fildes);
	clearerr(file);
	if((flags = _fopen_mode(mode)) == -1
			|| (file->fildes = open(path, file->flags)) < 0)
		return NULL;
	file->flags = flags;
	return file;
}


/* fwrite */
size_t fwrite(void const * ptr, size_t size, size_t nb, FILE * file)
{
	char const * p = (char const *)ptr;
	size_t i;
	size_t j;
	size_t len;
	ssize_t w;

	for(i = 0; i < nb; i++)
		for(j = 0; j < size; j+=len)
		{
			len = min(BUFSIZ - file->len, size - j);
			memcpy(&file->buf[file->len], p, len);
			p += len;
			file->len += len;
			if(file->len != BUFSIZ) /* buffer is not full */
				continue;
			if((w = write(file->fildes, file->buf, BUFSIZ)) == -1)
				return i;
			memmove(file->buf, &file->buf[w], BUFSIZ - w);
			file->len -= w;
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


/* vfprintf */
typedef int (*print_func)(void * dest, size_t size, const char * buf);
static int _fprint(void * dest, size_t size, const char * buf);
static int _vprintf(print_func func, void * dest, size_t size,
		char const * format, va_list arg);

int vfprintf(FILE * file, char const * format, va_list arg)
{
	size_t len = -1;

	return _vprintf(_fprint, file, len, format, arg);
}

static int _fprint(void * dest, size_t size, char const buf[])
{
	FILE * fp = dest;

	return fwrite(buf, sizeof(char), size, fp);
}

/* _vprintf */
static int _vprintf_format(print_func func, void * dest, size_t size,
		char const ** p, size_t * len, va_list * arg);

static int _vprintf(print_func func, void * dest, size_t size,
		char const * format, va_list arg)
{
	int ret = 0;
	char const * p;		/* pointer to current format character */
	size_t len;		/* length of the current element */

	for(p = format; *p != '\0'; p++)
	{
		if(*p != '%' || *++p == '%')
		{
			if((len = func(dest, sizeof(char), p)) != sizeof(char))
				return -1;
		}
		else if(_vprintf_format(func, dest, size, &p, &len, &arg) != 0)
				return -1;
		size = size > len ? size - len : 0; /* prevent overflow */
		if((ret += len) < 0) /* overflowing ret is an error */
		{
			errno = ERANGE;
			return -1;
		}
	}
	return ret;
}

static void _format_lutoa(char * dest, unsigned long n, size_t base);
static int _format_c(print_func func, void * dest, size_t * len, char * chrp);
static int _format_d(print_func func, void * dest, size_t size, size_t * len,
		long long * ptr);
static int _format_s(print_func func, void * dest, size_t size, size_t * len,
		char * str);
static int _format_p(print_func func, void * dest, size_t size, size_t * len,
		void * ptr);
static int _format_u(print_func func, void * dest, size_t size, size_t * len,
		unsigned long long * ptr);
static int _format_x(print_func func, void * dest, size_t size, size_t * len,
		unsigned long long * ptr);
static int _vprintf_format(print_func func, void * dest, size_t size,
		char const ** p, size_t * len, va_list * arg)
{
	char c;
	char * str;
	long long int i;
	void * ptr;
	int lng = 0;

	for(; **p != '\0';)
	{
		switch(**p)
		{
			case '0': /* FIXME implement */
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case ' ':
			case '.':
				(*p)++;
				continue;
			case 'l':
				lng++;
				(*p)++;
				continue;
			case 'c':
				c = va_arg(*arg, char);
				if(_format_c(func, dest, len, &c) == -1)
					return -1;
				break;
			case 'd':
				i = lng > 1 ? va_arg(*arg, long long int)
					: (lng == 1 ? va_arg(*arg, long int)
							: va_arg(*arg, int));
				if(_format_d(func, dest, size, len, &i) == -1)
					return -1;
				break;
			case 's':
				str = va_arg(*arg, char*);
				if(_format_s(func, dest, size, len, str) == -1)
					return -1;
				break;
			case 'p':
				ptr = va_arg(*arg, void*);
				if(_format_p(func, dest, size, len, ptr) == -1)
					return -1;
				break;
			case 'u':
				i = lng > 1 ? va_arg(*arg, long long int)
					: (lng == 1 ? va_arg(*arg, long int)
							: va_arg(*arg, int));
				if(_format_u(func, dest, size, len, &i) == -1)
					return -1;
				break;
			case 'x':
				i = lng > 1 ? va_arg(*arg, long long int)
					: (lng == 1 ? va_arg(*arg, long int)
							: va_arg(*arg, int));
				if(_format_x(func, dest, size, len, &i) == -1)
					return -1;
				break;
			default:
				errno = ENOSYS;
				return -1;
		}
		break;
	}
	return 0;
}

static int _format_c(print_func func, void * dest, size_t * len, char * chrp)
{
	if(func(dest, 1, chrp) != 1)
		return -1;
	*len = 1;
	return 0;
}

static int _format_d(print_func func, void * dest, size_t size, size_t * len,
		long long * ptr)
{
	long long val;

	if(*ptr >= 0)
		return _format_u(func, dest, size - 1, len, ptr);
	val = -(*ptr);
	if(func(dest, 1, "-") != 1
			|| _format_u(func, dest, size - 1, len, &val) == -1)
		return -1;
	(*len)++;
	return 0;
}

static int _format_s(print_func func, void * dest, size_t size, size_t * len,
		char * str)
{
	int l;

	*len = strlen(str);
	l = min(strlen(str), size);
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
	char conv[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	size_t len = 0;
	long p = n;
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
