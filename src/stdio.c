/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#include "errno.h"
#include "fcntl.h"
#include "unistd.h"
#include "stdarg.h"
#include "stdlib.h"
#include "string.h"
#include "limits.h"
#include "stdio.h"

#define min(a, b) ((a) > (b) ? (b) : (a))


/* types */
struct _FILE
{
	int fildes;
	char flags;
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
		return 0;
	else if(file->flags & O_RDWR)
	{
		errno = ENOSYS;
		return EOF;
	}
	if((count = file->len - file->pos) == 0)
		return 0;
	/* FIXME should loop until completion or an error occurs */
	if(write(file->fildes, file->buf, count) != count)
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
static int _fopen_mode(char const * mode);
FILE * fopen(char const * path, char const * mode)
{
	FILE * fp;

	if((fp = malloc(sizeof(FILE))) == NULL)
		return NULL;
	if((fp->flags = _fopen_mode(mode)) == -1)
	{
		free(fp);
		return NULL;
	}
	if((fp->fildes = open(path, fp->flags)) != 0)
	{
		free(fp);
		return NULL;
	}
	fp->len = 0;
	fp->pos = 0;
	fp->eof = 0;
	return fp;
}

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
		return -1;
	if(*mode != '\0')
		return -1;
	return flags;
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


/* fwrite */
size_t fwrite(void const * ptr, size_t size, size_t nb, FILE * file)
{
	size_t pos;
	ssize_t len;

	for(pos = 0; pos < size * nb; pos+=len)
	{
		len = min(BUFSIZ - file->len, (size * nb) - pos);
		memcpy(&file->buf[file->len], ptr + pos, len);
		file->len+=len;
		if(file->len != BUFSIZ)
			return nb;
		if((len = write(file->fildes, file->buf, file->len)) == 0)
			return pos / size;
		if(len == -1)
			return -1;
		memmove(file->buf, &file->buf[len], BUFSIZ - len);
		file->len-=len;
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
typedef int (*print_func)(void * dest, size_t size, char const buf[]);
static int _vprintf(print_func func, void * dest, size_t size,
		char const * format, va_list arg);
static int _fprint(void * dest, size_t size, char const buf[]);
static void _vprintf_lutoa(char * dest, long unsigned n, size_t base);

int vfprintf(FILE * file, char const * format, va_list arg)
{
	size_t len = -1;

	return _vprintf(_fprint, file, len, format, arg);
}

/* _vprintf */
static int _vprintf_s(print_func func, void * dest, size_t size, size_t * len,
		va_list arg);
static int _vprintf_p(print_func func, void * dest, size_t size, size_t * len,
		va_list arg);
static int _vprintf_u(print_func func, void * dest, size_t size, size_t * len,
		va_list arg);

static int _vprintf(print_func func, void * dest, size_t size,
		char const * format, va_list arg)
{
	int ret = 0;
	char const * p;		/* pointer to current format character */
	size_t len;		/* length of the current element */

	for(p = format; *p != '\0'; p++)
	{
		if(*p != '%')
		{
			if((len = func(dest, sizeof(char), p)) != sizeof(char))
				return -1;
		}
		else
			switch(*++p) /* FIXME implement properly */
			{
				case 's':
					if(_vprintf_s(func, dest, size, &len,
								arg) == -1)
						return -1;
					break;
				case 'p':
					if(_vprintf_p(func, dest, size, &len,
								arg) == -1)
						return -1;
					break;
				case 'u':
					if(_vprintf_u(func, dest, size, &len,
								arg) == -1)
						return -1;
					break;
				default:
					errno = ENOSYS;
					return -1;
			}
		size = size > len ? size - len : 0; /* prevent overflow */
		if(ret + len <= 0) /* overflowing ret is an error */
		{
			errno = ERANGE;
			return -1;
		}
		ret+=len;
	}
	if(size > 0 && func(dest, 1, "") != 1) /* end string if possible */
		return -1;
	return ret;
}

static int _fprint(void * dest, size_t size, char const buf[])
{
	FILE * fp = dest;

	return fwrite(buf, sizeof(char), size, fp);
}

static int _vprintf_s(print_func func, void * dest, size_t size, size_t * len,
		va_list arg)
{
	char * str;
	int l;

	str = va_arg(arg, char *);
	*len = strlen(str);
	l = min(strlen(str), size);
	if(func(dest, l, str) != l)
		return -1;
	return 0;
}

static int _vprintf_p(print_func func, void * dest, size_t size, size_t * len,
		va_list arg)
{
	void * ptr;
	char tmp[3 + sizeof(void*) + sizeof(void*)] = "0x";
	int l;

	ptr = va_arg(arg, void *);
	*len = sizeof(tmp);
	l = min(sizeof(tmp), size);
	_vprintf_lutoa(&tmp[2], (long)ptr, 16); /* XXX cast */
	if(func(dest, l, tmp) != l)
		return -1;
	return 0;
}

static int _vprintf_u(print_func func, void * dest, size_t size, size_t * len,
		va_list arg)
{
	unsigned long uns;
	char tmp[19] = "";
	int l;

	uns = va_arg(arg, unsigned long);
	_vprintf_lutoa(tmp, uns, 10); /* XXX assumes tmp is large enough */
	*len = strlen(tmp);
	l = min(*len, size);
	if(func(dest, l, tmp) != l)
		return -1;
	return 0;
}

/* PRE	dest is long enough
 * POST	2 <= base <= 36		dest is the ascii representation of n
 *	else			dest is an empty string */
static void _vprintf_lutoa(char * dest, long unsigned n, size_t base)
{
	char conv[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	size_t len;
	long p = n;
	size_t i = 0;

	if(base < 2 || base >= sizeof(conv))
	{
		dest[0] = '\0';
		return;
	}
	/* XXX performing twice the divisions is not optimal */
	for(p = n; p > 0; p /= base)
		len++;
	for(; n > 0; n /= base)
	{
		p = n % base;
		dest[i++] = conv[p];
		n -= p;
	}
	dest[i] = '\0';
}


/* vsnprintf */
static int _sprint(void * dest, size_t size, char const buf[]);
int vsnprintf(char * str, size_t size, char const * format, va_list arg)
{
	return _vprintf(_sprint, &str, size, format, arg);
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
	size_t size = -1;

	return _vprintf(_sprint, &str, size, format, arg);
}
