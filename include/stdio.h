/* stdio.h */
/* standard buffered input/output */



#ifndef ___STDIO_H
# define ___STDIO_H

# include "stddef.h"


/* constants */
/* size of <stdio.h> buffers */
# define BUFSIZ 8192

/* end-of-file return value */
# define EOF (-1)


/* types */
typedef struct _FILE {
	int fildes;
	int flags;
	unsigned char buf[BUFSIZ];
	int len;
	int pos;
} FILE;


/* variables */
/* standard input, output, and error streams */
extern FILE * stdin;
extern FILE * stdout;
extern FILE * stderr;


/* functions */
int fclose(FILE * stream);
FILE * fdopen(int fildes, char const * mode);
int fflush(FILE * stream);
int fgetc(FILE * stream);
FILE * fopen(char const * path, char const * mode);
int fprintf(FILE * stream, char const * format, ...);
int fputc(int c, FILE * stream);
size_t fread(void * ptr, size_t size, size_t nb, FILE * file);
size_t fwrite(void * ptr, size_t size, size_t nb, FILE * file);
int getc(FILE * stream);
int getchar(void);
int printf(char const * format, ...);
int puts(char const *string);

#endif /* !___STDIO_H */
