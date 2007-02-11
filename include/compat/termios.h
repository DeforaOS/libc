/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_COMPAT_TERMIOS_H
# define LIBC_COMPAT_TERMIOS_H


# if defined(__linux__)
#  include "kernel/linux/termios.h"
# elif defined(__NetBSD__)
#  include "kernel/netbsd/termios.h"
# else
#  warning Unsupported platform
# endif

#endif /* !LIBC_COMPAT_TERMIOS_H */
