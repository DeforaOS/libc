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



#ifndef LIBC_SYS_SHM_H
# define LIBC_SYS_SHM_H

# include "compat/sys/shm.h"
# include "ipc.h"


/* types */
# ifndef pid_t
#  define pid_t pid_t
typedef signed int pid_t;
# endif
# ifndef size_t
#  define size_t size_t
typedef unsigned long size_t;
# endif
# ifndef smhid_ds
#  define shmid_ds shmid_ds
struct shmid_ds
{
	/* FIXME implement */
};
# endif


/* constants */
# define SHM_RDONLY		010000


/* functions */
void * shmat(int shmid, const void * shmaddr, int shmflag);
int shmctl(int shmid, int cmd, struct shmid_ds * buf);
int shmdt(const void * shmaddr);
int shmget(key_t key, size_t size, int shmflag);

#endif /* !LIBC_SYS_SHM_H */
