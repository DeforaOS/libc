/* string.h */
/* string operations */



#ifndef ___STRING_H
# define ___STRING_H


#include "stddef.h"

/* function prototypes */
void * memcpy(void * dest, void const * src, size_t n);
void * memmove(void * dest, void const * src, size_t n);
void * memset(void * dest, int c, size_t n);
char * strcat(char * dest, char const * src);
int strcmp(char const * s1, char const * s2);
char * strcpy(char * dest, char const * src);
char * strdup(char const * s);
size_t strlen(char const * s);
char * strncat(char * dest, char const * src, size_t n);
int strncmp(char const * s1, char const * s2, size_t n);
char * strncpy(char * dest, char const * src, size_t n);

#endif
