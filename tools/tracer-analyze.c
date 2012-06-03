/* $Id$ */
/* Copyright (c) 2012 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. */



#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "tracer-syscalls.h"
#include "../src/syscalls.h"


/* private */
/* constants */
static const struct
{
	int number;
	char const * name;
}
_syscalls[] =
{
	{ SYS_access,		"access"	},
#ifdef SYS_brk
	{ SYS_brk,		"brk"		},
#endif
	{ SYS_chmod,		"chmod"		},
	{ SYS_chown,		"chown"		},
	{ SYS_close,		"close"		},
	{ SYS_dup,		"dup"		},
#ifdef SYS_dup2
	{ SYS_dup2,		"dup2"		},
#endif
	{ SYS_execve,		"execve"	},
	{ SYS_exit,		"_exit"		},
#ifdef SYS_fchdir
	{ SYS_fchdir,		"fchdir"	},
#endif
	{ SYS_fchmod,		"fchmod"	},
	{ SYS_fchown,		"fchown"	},
	{ SYS_fcntl,		"fcntl"		},
#ifdef SYS_flock
	{ SYS_flock,		"flock"		},
#endif
	{ SYS_fork,		"fork"		},
	{ SYS_fstat,		"fstat"		},
#ifdef SYS_fsync
	{ SYS_fsync,		"fsync"		},
#endif
#ifdef SYS_getdents
	{ SYS_getdents,		"getdents"	},
#endif
#ifdef SYS_getegid
	{ SYS_getegid,		"getegid"	},
#endif
#ifdef SYS_geteuid
	{ SYS_geteuid,		"geteuid"	},
#endif
	{ SYS_getgid,		"getgid"	},
	{ SYS_getpid,		"getpid"	},
#ifdef SYS_getppid
	{ SYS_getppid,		"getppid"	},
#endif
#ifdef SYS_getpriority
	{ SYS_getpriority,	"getpriority"	},
#endif
#ifdef SYS_getrlimit
	{ SYS_getrlimit,	"getrlimit"	},
#endif
#ifdef SYS_getrusage
	{ SYS_getrusage,	"getrusage"	},
#endif
	{ SYS_getuid,		"getuid"	},
#ifdef SYS_ioctl
	{ SYS_ioctl,		"ioctl"		},
#endif
	{ SYS_kill,		"kill"		},
	{ SYS_lchown,		"lchown"	},
	{ SYS_link,		"link"		},
	{ SYS_lstat,		"lstat"		},
	{ SYS_mknod,		"mknod"		},
#ifdef SYS_mlock
	{ SYS_mlock,		"mlock"		},
#endif
	{ SYS_mmap,		"mmap"		},
#ifdef SYS_mprotect
	{ SYS_mprotect,		"mprotect"	},
#endif
	{ SYS_munmap,		"munmap"	},
	{ SYS_open,		"open"		},
	{ SYS_pipe,		"pipe"		},
#ifdef SYS_poll
	{ SYS_poll,		"poll"		},
#endif
	{ SYS_read,		"read"		},
	{ SYS_readlink,		"readlink"	},
#ifdef SYS_select
	{ SYS_select,		"select"	},
#endif
	{ SYS_setgid,		"setgid"	},
#ifdef SYS_setpriority
	{ SYS_setpriority,	"setpriority"	},
#endif
	{ SYS_setregid,		"setregid"	},
	{ SYS_setreuid,		"setreuid"	},
#ifdef SYS_setrlimit
	{ SYS_setrlimit,	"setrlimit"	},
#endif
	{ SYS_setuid,		"setuid"	},
	{ SYS_stat,		"stat"		},
	{ SYS_symlink,		"symlink"	},
	{ SYS_sync,		"sync"		},
#ifdef SYS_sysctl
	{ SYS_sysctl,		"sysctl"	},
#endif
	{ SYS_umask,		"umask"		},
	{ SYS_unlink,		"unlink"	},
#ifdef SYS_wait4
	{ SYS_wait4,		"wait4"		},
#endif
#ifdef SYS_waitpid
	{ SYS_waitpid,		"waitpid"	},
#endif
	{ SYS_write,		"write"		}
};


/* prototypes */
static void _analyze_print(char const * str);


/* public */
/* functions */
void analyze(int number, long arg1, long arg2)
{
	size_t i;
	char buf[256];
	char const * s;

	_analyze_print("tracer: syscall: ");
	snprintf(buf, sizeof(buf), "%d", number);
	for(i = 0; i < sizeof(_syscalls) / sizeof(*_syscalls); i++)
		if(_syscalls[i].number == number)
		{
			snprintf(buf, sizeof(buf), "%s", _syscalls[i].name);
			break;
		}
	_analyze_print(buf);
	switch(number)
	{
		case SYS_access:
			/* FIXME analyze mode */
			s = (char const *)arg1;
			snprintf(buf, sizeof(buf), "(\"%s\", %u)\n", s, arg2);
			break;
		case SYS_close:
		case SYS_exit:
#ifdef SYS_fchdir
		case SYS_fchdir:
#endif
		case SYS_fstat:
#ifdef SYS_fsync
		case SYS_fsync:
#endif
			snprintf(buf, sizeof(buf), "(%d)\n", arg1);
			break;
		case SYS_execve:
			/* FIXME analyze the arguments and environment */
			s = (char const *)arg1;
			snprintf(buf, sizeof(buf), "(\"%s\")\n", s);
		case SYS_fcntl:
#ifdef SYS_flock
		case SYS_flock:
#endif
			snprintf(buf, sizeof(buf), "(%d, %d)\n", arg1, arg2);
			break;
#ifdef SYS_ioctl
		case SYS_ioctl:
			snprintf(buf, sizeof(buf), "(%d, %lu)\n", arg1, arg2);
			break;
#endif
		case SYS_lstat:
		case SYS_stat:
			s = (char const *)arg1;
			snprintf(buf, sizeof(buf), "(\"%s\")\n", s);
			break;
		case SYS_munmap:
			snprintf(buf, sizeof(buf), "(%p, %lu)\n", arg1, arg2);
			break;
		case SYS_open:
			/* FIXME analyze flags */
			s = (char const *)arg1;
			snprintf(buf, sizeof(buf), "(\"%s\", %u)\n", s, arg2);
			break;
#ifdef SYS_sysctl
		case SYS_sysctl:
			/* FIXME analyze the name */
			snprintf(buf, sizeof(buf), "(%p, %u)\n", arg1, arg2);
			break;
#endif
		default:
			snprintf(buf, sizeof(buf), "()\n");
			break;
	}
	_analyze_print(buf);
}


/* private */
/* functions */
static void _analyze_print(char const * str)
{
	size_t len;

	len = strlen(str);
	syscall(SYS_write, STDERR_FILENO, str, len);
}
