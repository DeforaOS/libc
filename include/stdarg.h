/* stdarg.h */
/* handle variable argument list */



#ifndef ___STDARG_H
# define ___STDARG_H


/* types */
# ifndef va_list
#  define va_list va_list
typedef void * va_list;
# endif


/* macros */
# define va_start(ap, arg) (ap) = (arg)
# define va_arg(ap, type) ((ap) += sizeof(type))
# define va_end(ap)

#endif /* !___STDARG_H */
