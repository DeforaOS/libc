/* unistd.c */



#include "sys/types.h"
#include "syscalls.h"
#include "stddef.h"


/* access */
syscall2(int, access, const char *, filename, int, mode);


/* alarm */
syscall1(unsigned int, alarm, unsigned int, seconds);


/* brk */
syscall1(int, brk, void *, end_data_segment);


/* chdir */
syscall1(int, chdir, char const *, filename);


/* chown */
syscall3(int, chown, char const *, filename, uid_t, owner, gid_t, group);


/* close */
syscall1(int, close, int, fildes);


/* dup */
syscall1(int, dup, int, fildes);


/* dup2 */
syscall2(int, dup2, int, fildes1, int, fildes2);


/* execve */
syscall3(int, execve, char const *, filename, char const **, argv,
		char const **, envp);


/* exit */
syscall1(void, exit, int, status);
void (* _exit)(int) = exit;


/* fork */
syscall0(pid_t, fork);


/* getegid */
syscall0(gid_t, getegid);


/* geteuid */
syscall0(uid_t, geteuid);


/* getpid */
syscall0(pid_t, getpid);


/* getppid */
syscall0(pid_t, getppid);


/* getuid */
syscall0(uid_t, getuid);


/* link */
syscall2(int, link, char const *, from, char const *, to);


/* nice */
syscall1(int, nice, int, inc);


/* pipe */
syscall1(int, pipe, int, filedes[2]);


/* read */
syscall3(ssize_t, read, int, fd, void *, buf, size_t, count);


/* readlink */
syscall3(ssize_t, readlink, char const *, filename, char *, buf,
		size_t, bufsiz);


/* rmdir */
syscall1(int, rmdir, char const *, filename);


/* sbrk */
void * sbrk(unsigned int increment) /* FIXME */
{
	return NULL;
}


/* setgid */
syscall1(int, setgid, gid_t, gid);


/* setpgid */
syscall2(int, setpgid, pid_t, pid, pid_t, pgid);


/* setregid */
syscall2(int, setregid, gid_t, rgid, gid_t, egid);


/* setreuid */
syscall2(int, setreuid, uid_t, ruid, uid_t, euid);


/* setsid */
syscall0(pid_t, setsid);


/* setuid */
syscall1(int, setuid, uid_t, uid);


/* symlink */
syscall2(int, symlink,char const *, from, char const *, to);


/* sync */
syscall0(void, sync);


/* unlink */
syscall1(int, unlink, const char *, filename);


/* vfork */
syscall0(pid_t, vfork);


/* write */
syscall3(ssize_t, write, int, fildes, const void *, buf, size_t, count);
