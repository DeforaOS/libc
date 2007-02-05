/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



.text


/* Linux */
#if defined(__linux__)
# include "kernel/linux/common.h"
# if defined(__i386__)
#  include "kernel/linux/i386/syscalls.S"
# elif defined(__sparc__)
#  include "kernel/linux/sparc/syscalls.S"
# else
#  warning Unsupported Linux architecture
# endif

/* NetBSD */
#elif defined(__NetBSD__)
# include "kernel/netbsd/common.h"
# if defined(__i386__)
#  include "kernel/netbsd/i386/syscalls.S"
# elif defined(__sparc__)
#  include "kernel/netbsd/sparc/syscalls.S"
# else
#  warning Unsupported NetBSD architecture
# endif
# include "kernel/netbsd/common.S"

/* Solaris */
#elif defined(__sun__)
# include "kernel/solaris/sparc/syscalls.S"
# include "kernel/solaris/common.h"

/* Unknown */
#else
# error Unsupported platform
#endif

/* dirent.h */
#ifdef SYS_readdir
SYSCALL(readdir)
#endif
#ifdef SYS_getdents
SYSCALL(getdents)
#endif

/* fcntl.h */
SYSCALL(fcntl)
SYSCALL(open)

/* signal.h */
SYSCALL(kill)

/* stdio.h */
SYSCALL(rename)

/* sys/mman.h */
#ifdef SYS_mmap
SYSCALL(mmap)
#endif
SYSCALL(munmap)

/* sys/select.h */
#ifdef SYS_select
SYSCALL(select)
#endif

/* sys/stat.h */
SYSCALL(chmod)
SYSCALL(fstat)
SYSCALL(lstat)
SYSCALL(mkdir)
#ifdef SYS_mkfifo
SYSCALL(mkfifo)
#endif
SYSCALL(mknod)
SYSCALL(stat)
SYSCALL(umask)

/* sys/statvfs.h */
#ifdef SYS_statfs
SYSCALL(statfs)
#endif
#ifdef SYS_statvfs
SYSCALL(statvfs)
#endif

/* sys/time.h */
SYSCALL(gettimeofday)
#ifdef SYS_utimes
SYSCALL(utimes)
#endif

/* sys/times.h */
#ifdef SYS_times
SYSCALL(times)
#endif

/* sys/utsname.h */
#ifdef SYS_uname
SYSCALL(uname)
#endif

/* sys/wait.h */
#ifdef SYS_wait
SYSCALL(wait)
#endif
#ifdef SYS_waitpid
SYSCALL(waitpid)
#elif defined(SYS_wait4)
SYSCALL(wait4)
#endif /* !SYS_waitpid && SYS_wait4) */

/* time.h */
SYSCALL(nanosleep)

/* unistd.h */
SYSCALL(access)
#ifdef SYS_alarm
SYSCALL(alarm)
#endif
#ifdef SYS_brk
SYSCALL(brk)
#endif
SYSCALL(chdir)
SYSCALL(chown)
SYSCALL(close)
SYSCALL(dup)
#ifdef SYS_dup2
SYSCALL(dup2)
#endif
#ifdef SYS_execve
SYSCALL(execve)
#endif
SYSCALL(fork)
SYSCALL(getcwd)
#ifdef SYS_getegid
SYSCALL(getegid)
#endif
#ifdef SYS_geteuid
SYSCALL(geteuid)
#endif
SYSCALL(getgid)
SYSCALL(getpid)
#ifdef SYS_getppid
SYSCALL(getppid)
#endif
SYSCALL(getuid)
SYSCALL(lchown)
SYSCALL(link)
#ifdef SYS_nice
SYSCALL(nice)
#endif
SYSCALL(pipe)
SYSCALL(read)
SYSCALL(readlink)
SYSCALL(rmdir)
#ifdef SYS_sbrk
SYSCALL(sbrk)
#endif
SYSCALL(setgid)
#ifdef SYS_setpgid
SYSCALL(setpgid)
#endif
SYSCALL(setregid)
SYSCALL(setreuid)
#ifdef SYS_setsid
SYSCALL(setsid)
#endif
SYSCALL(setuid)
SYSCALL(symlink)
SYSCALL(sync)
SYSCALL(unlink)
SYSCALL(vfork)
SYSCALL(write)

/* utime.h */
#ifdef SYS_utime
SYSCALL(utime)
#endif
