/* stddef.h */
/* standard type definitions */



#ifndef ___STDDEF_H
# define ___STDDEF_H


/* null pointer */
#ifndef NULL
# define NULL ((void*)0)
#endif

/* largest character set supported */
typedef char wchar_t;

/* result of the sizeof operator */
#ifndef size_t
# define size_t size_t
typedef unsigned int size_t;
#endif

#endif /* ___STDDEF_H */
