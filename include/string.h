/* string.h */
/* string operations */



#ifndef ___STRING_H
# define ___STRING_H

# include "stddef.h"


/* function prototypes */
int memcmp(void const * s1, void const * s2, size_t n);
void * memcpy(void * dest, void const * src, size_t n);
void * memmove(void * dest, void const * src, size_t n);
void * memset(void * dest, int c, size_t n);
char * strcat(char * dest, char const * src);
char * strchr(char const * s, int c);
int strcmp(char const * s1, char const * s2);
char * strcpy(char * dest, char const * src);
size_t strcspn(char const * s1, char const * s2);
char * strdup(char const * s);
char * strerror(int errnum);
size_t strlen(char const * s);
char * strncat(char * dest, char const * src, size_t n);
int strncmp(char const * s1, char const * s2, size_t n);
char * strncpy(char * dest, char const * src, size_t n);
char * strrchr(char const * s, int c);
char * strstr(char const * s1, char const * s2);
char * strtok(char * s1, char const * s2);

#endif /* !___STRING_H */
