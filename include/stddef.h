/* stddef.h */
/* standard type definitions */



#ifndef ___STDDEF_H
# define ___STDDEF_H


/* types */
# ifndef size_t
#  define size_t size_t
typedef unsigned int size_t;
# endif
typedef char wchar_t;


/* constants */
# ifndef NULL
#  define NULL ((void*)0)
# endif

#endif /* !___STDDEF_H */
