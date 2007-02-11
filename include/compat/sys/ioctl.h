/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_COMPAT_SYS_IOCTL_H
# define LIBC_COMPAT_SYS_IOCTL_H


# if defined(__linux__)
#  include "kernel/linux/sys/ioctl.h"
# elif defined(__NetBSD__)
#  include "kernel/netbsd/sys/ioctl.h"
# else
#  warning Unsupported platform
# endif

#endif /* !LIBC_COMPAT_SYS_IOCTL_H */
