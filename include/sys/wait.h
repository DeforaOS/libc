/* $Id$ */
/* Copyright (c) 2005-2017 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */



#ifndef LIBC_SYS_WAIT_H
# define LIBC_SYS_WAIT_H

# include "../compat.h"


/* types */
# ifndef id_t
#  define id_t id_t
typedef __id_t id_t;
# endif
typedef enum { P_ALL, P_PID, P_PGID } idtype_t;
# ifndef pid_t
#  define pid_t pid_t
typedef __pid_t pid_t;
# endif
/* FIXME rusage */


/* constants */
# define WNOHANG	0		/* FIXME */
# define WUNTRACED	0		/* FIXME */

# define WEXITSTATUS(status)	((status >> 8) & 0xff)
# define WIFCONTINUED(status)	(0)	/* FIXME */
# define WIFEXITED(status)	((status & 0x7f) == 0x00)
# define WIFSIGNALED(status)	((status & 0x7f) != 0x7f \
		&& (status & 0x7f) != 0x00)
# define WIFSTOPPED(status)	((status & 0x7f) == 0x7f)
# define WSTOPSIG(status)	((status >> 8) & 0xff)
# define WTERMSIG(status)	(status & 0x7f)

# define WEXITED	0		/* FIXME */
# define WSTOPPED	0		/* FIXME */
# define WCONTINUED	0		/* FIXME */
# define WNOWAIT	0		/* FIXME */


/* functions */
pid_t wait(int * status);
pid_t waitpid(pid_t pid, int * status, int options);

#endif
