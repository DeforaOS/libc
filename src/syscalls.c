/* syscalls.c */



#include <linux/types.h>
#include <errno.h>
#include <asm/unistd.h>


/* syscall0 */
_syscall0(pid_t, fork);
_syscall0(gid_t, getegid);
_syscall0(uid_t, geteuid);
_syscall0(gid_t, getgid);
_syscall0(pid_t, getpid);
_syscall0(uid_t, getuid);


/* syscall1 */
_syscall1(unsigned, alarm, unsigned, seconds);
_syscall1(int, close, int, fildes);
_syscall1(int, dup, int, fildes);
/* FIXME _syscall1(void, exit, int, status); */
/* FIXME _syscall1(int, uname, struct utsname *, name); */
_syscall1(time_t, time, time_t *, tloc);
_syscall1(int, unlink, const char *, path);


/* syscall2 */
_syscall2(int, chmod, const char *, path, mode_t, mode);
_syscall2(int, creat, const char *, path, mode_t, mode);
_syscall2(int, dup2, int, fildes, int, fildes2);
_syscall2(char *, getcwd, char *, buf, size_t, size);
_syscall2(int, kill, pid_t, pid, int, sig);
_syscall2(int, link, const char *, path1, const char *, path2);
/* FIXME
_syscall2(off_t, lstat, const char * restrict, path,
		struct stat * restrict, buf); */
/* FIXME _syscall2(off_t, lstat, const char *, path, struct stat *, buf); */
_syscall2(int, mkdir, const char *, path, mode_t, mode);


/* syscall3 */
/* _syscall3(int, open, const char *, pathname, int, flags, mode_t, mode); */
_syscall3(int, execve, const char *, path, char * const *, argv,
		char * const *, envp);
_syscall3(int, lchown, const char *, path, uid_t, owner, gid_t, group);
_syscall3(off_t, lseek, int, fildes, off_t, offset, int, whence);
_syscall3(int, mknod, const char *, path, mode_t, mode, dev_t, dev);
_syscall3(ssize_t, read, int, fildes, void *, buf, size_t, nbyte);
_syscall3(pid_t, waitpid, pid_t, pid, int *, stat_loc, int, options);
_syscall3(ssize_t, write, int, fildes, const void *, buf, size_t, nbyte);
