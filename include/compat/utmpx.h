/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_COMPAT_UTMPX_H
# define LIBC_COMPAT_UTMPX_H


# if defined(__linux__)
#  include "kernel/linux/utmpx.h"
# elif defined(__NetBSD__)
#  include "kernel/netbsd/utmpx.h"
# else
#  warning Unsupported platform
# endif

#endif /* !LIBC_COMPAT_UTMPX_H */
