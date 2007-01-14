/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#include "../syscalls.h"
#include "errno.h"
#include "sys/mman.h"


/* mmap */
/* FIXME ugly hack for addresses >= 0x80000000 */
void * mmap(void * start, size_t length, int prot, int flags, int fd,
		off_t offset)
{
	void * ret;

	ret = (void*)_syscall6(SYS_mmap, (int)start, length, prot, flags, fd,
			offset);
	if(ret == (void*)-1 && errno > 255)
		return (void*)-errno;
	return ret;
}


/* munmap */
syscall2(int, munmap, void *, start, size_t, length);
