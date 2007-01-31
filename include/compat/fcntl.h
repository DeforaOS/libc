/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_COMPAT_FCNTL_H
# define LIBC_COMPAT_FCNTL_H


# if defined(__linux__)
#  include "kernel/linux/fcntl.h"
# elif defined(__NetBSD__)
#  include "kernel/netbsd/fcntl.h"
# else
#  warning Unsupported platform
# endif

#endif /* !LIBC_COMPAT_FCNTL_H */
