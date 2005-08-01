/* stdlib.h */
/* standard library definitions */



#ifndef ___STDLIB_H
# define ___STDLIB_H

# include "stddef.h"


/* functions */
int atoi(char const * str);
long atol(char const * str);
long long atoll(char const * nptr);
void exit(int status);
void free(void * ptr);
char * getenv(char const * name);
void * malloc(size_t size);
void * realloc(void * ptr, size_t size);
int setenv(char const * name, char const * value, int overwrite);
long strtol(char const * str, char ** endptr, int base);
int unsetenv(char const * name);

#endif /* !___STDLIB_H */
