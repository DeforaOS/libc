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
# ifndef siginfo_t
#  define siginfo_t siginfo_t
typedef int siginfo_t; /* FIXME */
# endif


/* constants */
# define WNOHANG
# define WUNTRACED

# define WEXITSTATUS(status) { } /* FIXME */
# define WIFCONTINUED(status) { } /* FIXME */
# define WIFEXITED(status) { } /* FIXME */
# define WIFSIGNALED(status) { } /* FIXME */
# define WIFSTOPPED(status) { } /* FIXME */
# define WSTOPSIG(status) { } /* FIXME */
# define WTERMSIG(status) { } /* FIXME */

# define WEXITED
# define WSTOPPED
# define WCONTINUED
# define WNOHANG
# define WNOWAIT


/* functions */
pid_t wait(int * status);
int waitid(idtype_t idtype, id_t id, siginfo_t * siginfo, int options);
pid_t waitpid(pid_t pid, int * status, int options);

#endif
