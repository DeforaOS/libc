/* signal.h */



#ifndef ___SIGNAL_H
# define ___SIGNAL_H


/* types */
# ifndef id_t
#  define id_t id_t
typedef int id_t;
# endif
# ifndef pid_t
#  define pid_t pid_t
typedef id_t pid_t;
# endif


/* functions */
int kill(pid_t pid, int sig);

#endif /* !___SIGNAL_H */
