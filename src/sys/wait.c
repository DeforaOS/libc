/* sys/wait.c */



#include "../syscalls.h"
#include "sys/wait.h"


/* wait */
pid_t wait(int * status)
{
	return waitpid(-1, status, 0);
}


/* waitpid */
syscall3(pid_t, waitpid, pid_t, pid, int *, status, int, options)
