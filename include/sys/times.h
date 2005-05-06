/* sys/times.h */



#ifndef ___SYS_TIMES_H
# define ___SYS_TIMES_H


/* types */
# ifndef clock_t
#  define clock_t clock_t
typedef int clock_t;
# endif

struct tms
{
	clock_t tms_utime;
	clock_t tms_stime;
	clock_t tms_cutime;
	clock_t tms_cstime;
};


/* function */
clock_t times(struct tms * buf);

#endif /* !___SYS_TIMES_H */
