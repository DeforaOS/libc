/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_COMPAT_SYS_RESOURCE_H
# define LIBC_COMPAT_SYS_RESOURCE_H


# if defined(__linux__)
#  include "kernel/linux/sys/resource.h"
# elif defined(__NetBSD__)
#  include "kernel/netbsd/sys/resource.h"
# else
#  warning Unsupported platform
# endif

#endif /* !LIBC_COMPAT_SYS_RESOURCE_H */
