/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_COMPAT_SYS_MMAN_H
# define LIBC_COMPAT_SYS_MMAN_H


# if defined(__linux__)
#  include "kernel/linux/sys/mman.h"
# elif defined(__NetBSD__)
#  include "kernel/netbsd/sys/mman.h"
# elif defined(__sun__)
#  include "kernel/solaris/sys/mman.h"
# else
#  warning Unsupported platform
# endif

#endif /* !LIBC_COMPAT_SYS_MMAN_H */
