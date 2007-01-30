/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_COMPAT_DIRENT_H
# define LIBC_COMPAT_DIRENT_H


# if defined(__linux__)
#  include "kernel/linux/dirent.h"
# elif defined(__NetBSD__)
#  include "kernel/netbsd/dirent.h"
# else
#  warning Unsupported platform
# endif

#endif /* !LIBC_COMPAT_DIRENT_H */
