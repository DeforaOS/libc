/* stdio.c */



#include "errno.h"
#include "fcntl.h"
#include "unistd.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdarg.h"
#include "string.h"


/* variables */
FILE * stdin;
FILE * stdout;
FILE * stderr;


/* functions */
/* fclose */
int fclose(FILE * stream)
{
	int res;
	
	res = fflush(stream);
	close(stream->fildes);
	return res;
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
	return -1;
}


/* fwrite */
size_t fwrite(void * ptr, size_t size, size_t nb, FILE * file)
{
	return -1;
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
		fprintf(stdout, "%s%s", s, ": ");
	fprintf(stdout, "%s%s", strerror(errno), "\n");
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
	int i;

	for(i = 0; string[i] != '\0'; i++);
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
int vfprintf(FILE * stream, char const * format, va_list arg)
{
	return -1; /* FIXME */
}


/* vsprintf */
int vsprintf(char * str, char const * format, va_list arg)
{
	return -1; /* FIXME */
}
