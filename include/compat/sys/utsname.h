/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_COMPAT_SYS_UTSNAME_H
# define LIBC_COMPAT_SYS_UTSNAME_H


# if defined(__linux__)
#  include "kernel/linux/sys/utsname.h"
# elif defined(__NetBSD__)
#  include "kernel/netbsd/sys/utsname.h"
# else
#  error Unsupported platform
# endif

#endif /* !LIBC_COMPAT_SYS_UTSNAME_H */
