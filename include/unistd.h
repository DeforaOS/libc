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
extern char * optarg;
extern int optind, opterr, optopt;


/* functions */
int access(char const * filename, int mode);
unsigned int alarm(unsigned int seconds);
int brk(void * end_data_segment);
int chdir(char const * filename);
int chown(char const * filename, uid_t owner, gid_t group);
int close(int fildes);

int dup(int fildes);
int dup2(int fildes1, int fildes2);

int execve(char const * filename, char const * argv[], char const * envp[]);

void _exit(int status);

pid_t fork(void);

gid_t getegid(void);
uid_t geteuid(void);
gid_t getgid(void);

int getopt(int argc, char const * argv[], char const * optstring);

pid_t getpid(void);
pid_t getppid(void);

uid_t getuid(void);

int link(char const * from, char const * to);

int nice(int inc);

ssize_t read(int fildes, void * buf, size_t count);
ssize_t readlink(char const * filename, char * buf, size_t bufsiz);
int rmdir(char const * filename);

void * sbrk(size_t increment);

int setgid(gid_t gid);
int setpgid(pid_t pid, pid_t pgid);

int setregid(gid_t rgid, gid_t egid);
int setreuid(uid_t ruid, uid_t euid);
pid_t setsid(void);

int setuid(uid_t uid);

int symlink(char const * from, char const * to);
void sync(void);

int unlink(char const * filename);

pid_t vfork(void);
ssize_t write(int fildes, const void * buf, size_t count);

#endif /* !___UNISTD_H */
