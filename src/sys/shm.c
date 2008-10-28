/* $Id$ */
/* Copyright (c) 2008 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* libc is not free software; you can redistribute it and/or modify it under
 * the terms of the Creative Commons Attribution-NonCommercial-ShareAlike 3.0
 * Unported as published by the Creative Commons organization.
 *
 * libc is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the Creative Commons Attribution-NonCommercial-
 * ShareAlike 3.0 Unported license for more details.
 *
 * You should have received a copy of the Creative Commons Attribution-
 * NonCommercial-ShareAlike 3.0 along with libc; if not, browse to
 * http://creativecommons.org/licenses/by-nc-sa/3.0/ */



#include "errno.h"
#include "../syscalls.h"
#include "sys/shm.h"


/* functions */
/* shmat */
# ifndef SYS_shmat
# warning Unsupported platform: shmat() is missing
void * shmat(int shmid, const void * shmaddr, int shmflag)
{
	/* FIXME this return value may be considered legitimate */
	errno = ENOSYS;
	return NULL;
}
#endif


/* shmctl */
# ifndef SYS_shmctl
# warning Unsupported platform: shmctl() is missing
int shmctl(int shmid, int cmd, struct shmid_ds * buf)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* shmdt */
# ifndef SYS_shmdt
# warning Unsupported platform: shmdt() is missing
int shmdt(const void * shmaddr)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* shmget */
# ifndef SYS_shmget
# warning Unsupported platform: shmget() is missing
int shmget(key_t key, size_t size, int shmflag)
{
	errno = ENOSYS;
	return -1;
}
#endif
