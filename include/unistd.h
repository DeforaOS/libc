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
int access(char const * filename, int mode);
unsigned int alarm(unsigned int seconds);
int chdir(char const * filename);
int chown(char const * filename, uid_t owner, gid_t group);
int close(int fildes);

int dup(int fildes);
int dup2(int fildes1, int fildes2);

/* exec */

pid_t fork(void);

gid_t getegid(void);
uid_t geteuid(void);
gid_t getgid(void);

pid_t getpid(void);
pid_t getppid(void);

uid_t getuid(void);

int link(char const * from, char const * to);

int nice(int inc);

ssize_t read(int fd, void * buf, size_t count);

int rmdir(char const * filename);

int symlink(char const * from, char const * to);
void sync(void);

int unlink(char const * filename);

#endif /* !___UNISTD_H */
