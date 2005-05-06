/* utime.h */



#ifndef ___UTIME_H
# define ___UTIME_H


/* types */
# ifndef time_t
#  define time_t time_t
typedef int time_t;
# endif

struct utimbuf
{
	time_t actime;
	time_t modtime;
};


/* functions */
int utime(char const * filename, struct utimbuf const * buf);

#endif /* !___UTIME_H */
