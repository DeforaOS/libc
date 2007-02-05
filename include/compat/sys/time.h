/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_COMPAT_SYS_TIME_H
# define LIBC_COMPAT_SYS_TIME_H


# if defined(__linux__)
#  include "kernel/linux/sys/time.h"
# elif defined(__NetBSD__)
#  include "kernel/netbsd/sys/time.h"
# elif defined(__sun__)
#  include "kernel/solaris/sys/time.h"
# else
#  warning Unsupported platform
# endif

#endif /* !LIBC_COMPAT_SYS_TIME_H */
