/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#ifndef LIBC_SYS_WAIT_H
# define LIBC_SYS_WAIT_H


/* types */
# ifndef id_t
#  define id_t id_t
typedef int id_t;
# endif
typedef enum { P_ALL, P_PID, P_PGID } idtype_t;
# ifndef pid_t
#  define pid_t pid_t
typedef id_t pid_t;
# endif
/* FIXME rusage */


/* constants */
# define WNOHANG	0		/* FIXME */
# define WUNTRACED	0		/* FIXME */

# define WEXITSTATUS(status)	((status >> 8) & 0xff)
# define WIFCONTINUED(status)	(0)	/* FIXME */
# define WIFEXITED(status)	((status & 0x7f) == 0x00)
# define WIFSIGNALED(status)	(0)	/* FIXME */
# define WIFSTOPPED(status)	((status & 0x7f) == 0x7f)
# define WSTOPSIG(status)	((status >> 8) & 0xff)
# define WTERMSIG(status)	(status & 0x7f)

# define WEXITED	0		/* FIXME */
# define WSTOPPED	0		/* FIXME */
# define WCONTINUED	0		/* FIXME */
# define WNOWAIT	0		/* FIXME */


/* functions */
pid_t wait(int * status);
pid_t waitpid(pid_t pid, int * status, int options);

#endif
