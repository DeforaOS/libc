/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#ifndef LIBC_SIGNAL_H
# define LIBC_SIGNAL_H


/* types */
# ifndef id_t
#  define id_t id_t
typedef int id_t;
# endif
# ifndef pid_t
#  define pid_t pid_t
typedef id_t pid_t;
# endif
# ifndef siginfo_t
#  define siginfo_t siginfo_t
typedef int siginfo_t; /* FIXME */
# endif


/* functions */
int kill(pid_t pid, int sig);

#endif /* !LIBC_SIGNAL_H */
