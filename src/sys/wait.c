/* sys/wait.c */



#include "../syscalls.h"
#include "sys/wait.h"


/* wait */
pid_t wait(int * status)
{
	return waitpid(-1, status, 0);
}


/* waitid */
syscall4(int, waitid, idtype_t, idtype, id_t, id, siginfo_t *, siginfo, int,
		options)


/* waitpid */
syscall3(pid_t, waitpid, pid_t, pid, int *, status, int, options)
