/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_SYS_RESOURCE_H
# define LIBC_SYS_RESOURCE_H

# include "compat/sys/resource.h"


/* types */
# ifndef id_t
#  define id_t id_t
typedef unsigned int id_t;
# endif


/* functions */
int getpriority(int which, id_t who);
int getrlimit(int resource, struct rlimit * rlp);
int getrusage(int who, struct rusage * rup);
int setpriority(int which, id_t who, int value);
int setrlimit(int resource, const struct rlimit * rlp);

#endif /* !LIBC_SYS_RESOURCE_H */
