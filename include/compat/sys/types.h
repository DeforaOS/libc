/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_COMPAT_SYS_TYPES_H
# define LIBC_COMPAT_SYS_TYPES_H


# if defined(__linux__)
#  include "kernel/linux/sys/types.h"
# elif defined(__NetBSD__)
#  include "kernel/netbsd/sys/types.h"
# elif defined(__sun__)
#  include "kernel/solaris/sys/types.h"
# else
#  warning Unsupported platform
# endif

#endif /* !LIBC_COMPAT_SYS_TYPES_H */
