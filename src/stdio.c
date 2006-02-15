/* stdio.c */



#include "errno.h"
#include "fcntl.h"
#include "unistd.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdarg.h"
#include "string.h"

#define min(a, b) ((a) > (b) ? (b) : (a))


/* types */
struct _FILE
{
	int fildes;
	int flags;
	unsigned char buf[BUFSIZ];
	unsigned int len;
	unsigned int pos;
	int eof;
};


/* variables */
static FILE _stdin;
FILE * stdin = &_stdin;
static FILE _stdout;
FILE * stdout = &_stdout;
static FILE _stderr;
FILE * stderr = &_stderr;


/* functions */
/* clearerr */
void clearerr(FILE * stream)
{
	stream->eof = 0;
}


/* fclose */
int fclose(FILE * stream)
{
	int res;
	
	res = fflush(stream);
	close(stream->fildes);
	return res;
}


/* feof */
int feof(FILE * stream)
{
	return stream->eof;
}


/* fflush */
int fflush(FILE * stream)
{
	ssize_t count;

	if(stream->flags & O_RDONLY)
		return 0;
	else if(stream->flags & O_RDWR)
	{
		errno = ENOSYS;
		return EOF;
	}
	count = stream->len - stream->pos;
	/* FIXME should loop until completion or an error occurs */
	if(write(stream->fildes, stream->buf, count) != count)
		return EOF;
	return 0;
}


/* fgetc */
int fgetc(FILE * stream)
{
	char c;

	if(fread(&c, sizeof(char), 1, stream) != 1)
		return EOF;
	return c;
}


/* fileno */
int fileno(FILE * stream)
{
	if(stream == NULL)
	{
		errno = EBADF;
		return -1;
	}
	return stream->fildes;
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
int fprintf(FILE * stream, char const * format, ...)
{
	va_list arg;
	int ret;

	va_start(arg, format);
	ret = vfprintf(stream, format, arg);
	va_end(arg);
	return ret;
}


/* fputc */
int fputc(int c, FILE * stream)
{
	return fwrite(&c, sizeof(char), 1, stream);
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
	cnt = file->len / size;
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
int getc(FILE * stream)
{
	return fgetc(stream);
}


/* perror */
void perror(char const * s)
{
	if(s != NULL && *s != '\0')
		fprintf(stderr, "%s%s", s, ": ");
	fprintf(stderr, "%s%s", strerror(errno), "\n");
}


/* printf */
int printf(char const * format, ...)
{
	va_list arg;
	int ret;

	va_start(arg, format);
	ret = vfprintf(stdout, format, arg);
	va_end(arg);
	return ret;
}


/* puts */
int puts(char const * string)
{
	int i = strlen(string);

	fwrite(string, sizeof(char), i, stdout);
	fputc('\n', stdout);
	return i;
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
static int _vprintf(print_func func, void * dest, char const * format,
		va_list arg);
static int _fprint(void * dest, size_t size, char const buf[]);
int vfprintf(FILE * stream, char const * format, va_list arg)
{
	return _vprintf(_fprint, stream, format, arg);
}

static int _vprintf(print_func func, void * dest, char const * format,
		va_list arg)
{
	char const * p;
	char * str;
	int len = 0;

	for(p = format; *p != '\0'; p++)
	{
		if(*p != '%')
		{
			func(dest, sizeof(char), p);
			len++;
			continue;
		}
		switch(*++p)
		{
			case 's':
				str = va_arg(arg, char *);
				len+=strlen(str);
				func(dest, strlen(str), str);
				break;
			default:
				len++;
				func(dest, sizeof(char), p);
				break;
		}
	}
	return len;
}

static int _fprint(void * dest, size_t size, char const buf[])
{
	FILE * fp = dest;

	return fwrite(buf, sizeof(char), size, fp);
}


/* vsprintf */
static int _sprint(void * dest, size_t size, char const buf[]);
int vsprintf(char * str, char const * format, va_list arg)
{
	return _vprintf(_sprint, &str, format, arg);
}

static int _sprint(void * dest, size_t size, char const buf[])
{
	char ** str = dest;

	strncpy(*str, buf, size);
	*str += size;
	return size;
}
