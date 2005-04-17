/* sys/mman.c */



#include "../syscalls.h"
#include "sys/mman.h"


/* mmap */
syscall6(void *, mmap, void *, start, size_t, length, int, prot, int, flags,
		int, fd, off_t, offset);


/* munmap */
syscall2(int, munmap, void *, start, size_t, length);
