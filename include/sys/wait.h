/* $Id$ */
/* Copyright (c) 2008 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_SYS_WAIT_H
# define LIBC_SYS_WAIT_H


/* types */
# ifndef id_t
#  define id_t id_t
typedef unsigned int id_t;
# endif
typedef enum { P_ALL, P_PID, P_PGID } idtype_t;
# ifndef pid_t
#  define pid_t pid_t
typedef signed int pid_t;
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
