/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#include "errno.h"
#include "../syscalls.h"
#include "sys/mman.h"


/* mmap */
#ifndef SYS_mmap
# warning Unsupported platform: mmap() is missing
#endif


/* munmap */
#ifndef SYS_munmap
# warning Unsupported platform: munmap() is missing
#endif
