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
typedef struct _FILE FILE;

# ifndef va_list
#  define va_list va_list
typedef void * va_list;
# endif


/* variables */
/* standard input, output, and error streams */
extern FILE * stdin;
extern FILE * stdout;
extern FILE * stderr;


/* functions */
void clearerr(FILE * stream);
int fclose(FILE * stream);
FILE * fdopen(int fildes, char const * mode);
int feof(FILE * stream);
int fflush(FILE * stream);
int fgetc(FILE * stream);
int fileno(FILE * stream);
FILE * fopen(char const * path, char const * mode);
int fprintf(FILE * stream, char const * format, ...);
int fputc(int c, FILE * stream);
size_t fread(void * ptr, size_t size, size_t nb, FILE * file);
size_t fwrite(void const * ptr, size_t size, size_t nb, FILE * file);
int getc(FILE * stream);
int getchar(void);
void perror(char const * s);
int printf(char const * format, ...);
int puts(char const * string);
int sprintf(char * str, char const * format, ...);
int snprintf(char * str, size_t n, char const * format, ...);
int vfprintf(FILE * stream, char const * format, va_list arg);
int vsprintf(char * str, char const * format, va_list arg);

#endif /* !___STDIO_H */
