/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
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



#include "unistd.h"
#include "string.h"
#include "errno.h"
#include "syscalls.h"
#include "signal.h"


/* functions */
/* kill */
#ifndef SYS_kill
# warning Unsupported platform: kill() is missing
int kill(pid_t pid, int sig)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* raise */
int raise(int sig)
{
	return kill(getpid(), sig);
}


/* sigaction */
#ifndef SYS_sigaction
# warning Unsupported platform: sigaction() is missing
int sigaction(int sig, const struct sigaction * act, struct sigaction * oact)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* sigemptyset */
#ifndef sigemptyset
int sigemptyset(sigset_t * set)
{
	/* XXX untested */
	memset(set, 0, sizeof(*set));
	return 0;
}
#endif


/* sigprocmask */
#ifndef SYS_sigprocmask
# warning Unsupported platform: sigprocmask() is missing
int sigprocmask(int how, const sigset_t * set, sigset_t * oset)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* signal */
#ifndef SYS_signal
void (*signal(int sig, void (*func)(int)))
{
	struct sigaction sa;
	struct sigaction osa;

	sa.sa_handler = func;
	sigemptyset(&sa.sa_mask);
	if(sigaction(sig, &sa, &osa) != 0)
		return SIG_ERR;
	return osa.sa_handler;
}
#endif /* !SYS_signal */
