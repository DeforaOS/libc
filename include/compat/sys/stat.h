/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_COMPAT_SYS_STAT_H
# define LIBC_COMPAT_SYS_STAT_H


# if defined(__linux__)
#  include "kernel/linux/sys/stat.h"
# elif defined(__NetBSD__)
#  include "kernel/netbsd/sys/stat.h"
# else
#  warning Unsupported platform
# endif

#endif /* !LIBC_COMPAT_SYS_STAT_H */
