/* stdio.c */



#include "errno.h"
#include "fcntl.h"
#include "unistd.h"
#include "stdlib.h"
#include "stdio.h"


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
	size_t count;

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
