/* unistd.h */
/* standard symbolic constants and types */



#ifndef ___UNISTD_H
# define ___UNISTD_H


/* constants */
/* for access() */
enum { F_OK, R_OK, W_OK, X_OK };

/* for lseek() and fcntl() */
enum { SEEK_CUR, SEEK_END, SEEK_SET };

/* file streams */
# define STDERR_FILENO 2
# define STDIN_FILENO 0
# define STDOUT_FILENO 1


/* types */
# include "sys/types.h"
# include "inttypes.h"


/* variables */


/* functions */
int close(int fildes);
int dup(int fildes);

pid_t fork(void);

pid_t getpid(void);

void sync(void);

#endif /* !___UNISTD_H */
