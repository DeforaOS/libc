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
void * malloc(size_t size);
void * realloc(void * ptr, size_t size);
long strtol(char const * str, char ** endptr, int base);

#endif /* !___STDLIB_H */
