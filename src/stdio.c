/* stdio.c */



#include "unistd.h"
#include "stdio.h"


/* fclose */
/* FIXME */
int fclose(FILE * stream)
{
	int res;
	
	res = fflush(stream);
	close(stream->fd);
	return res;
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


/* fputc */
int fputc(int c, FILE * stream)
{
	return fwrite(&c, sizeof(char), 1, stream);
}


/* getc */
int getc(FILE * stream)
{
	return fgetc(stream);
}
