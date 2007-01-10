/* $Id$ */



#ifndef LIBC_KERNEL_NETBSD_SYS_SYSCTL_H
# define LIBC_KERNEL_NETBSD_SYS_SYSCTL_H


/* types */
# ifndef size_t
#  define size_t size_t
typedef unsigned int size_t;
# endif


/* constants */
# ifndef NULL
#  define NULL ((void*)0)
# endif

/* sysctl name */
# define CTL_KERN	1
# define CTL_HW		6

# define KERN_OSTYPE	1
# define KERN_OSRELEASE	2
# define KERN_VERSION	4
# define KERN_HOSTNAME	10

# define HW_MACHINE	1


/* functions */
int sysctl(int * name, unsigned int namecnt, void * from, size_t * fromsize,
		void * to, size_t tosize);

#endif /* !LIBC_KERNEL_NETBSD_SYS_SYSCTL_H */
