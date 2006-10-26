/* sys/wait.h */


#ifndef ___SYS_WAIT_H
# define ___SYS_WAIT_H


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

# define WEXITSTATUS(status) (0)	/* FIXME */
# define WIFCONTINUED(status) (0)	/* FIXME */
# define WIFEXITED(status) (0)		/* FIXME */
# define WIFSIGNALED(status) (0)	/* FIXME */
# define WIFSTOPPED(status) (0)		/* FIXME */
# define WSTOPSIG(status) (0)		/* FIXME */
# define WTERMSIG(status) (0)		/* FIXME */

# define WEXITED	0		/* FIXME */
# define WSTOPPED	0		/* FIXME */
# define WCONTINUED	0		/* FIXME */
# define WNOWAIT	0		/* FIXME */


/* functions */
pid_t wait(int * status);
pid_t waitpid(pid_t pid, int * status, int options);

#endif
