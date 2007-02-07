/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#ifndef LIBC_SIGNAL_H
# define LIBC_SIGNAL_H

# include "compat/signal.h"


/* types */
# ifndef id_t
#  define id_t id_t
typedef unsigned int id_t;
# endif
# ifndef pid_t
#  define pid_t pid_t
typedef id_t pid_t;
# endif
# ifndef uid_t
#  define uid_t uid_t
typedef id_t uid_t;
# endif
# ifndef siginfo_t
#  define siginfo_t siginfo_t
typedef struct
{
	int si_signo;
	int si_code;
	int si_errno;
	pid_t si_pid;
	uid_t si_uid;
	void * si_addr;
	int si_status;
	long si_band;
} siginfo_t;
# endif


/* functions */
int kill(pid_t pid, int sig);
int raise(int sig);

#endif /* !LIBC_SIGNAL_H */
