/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_COMPAT_SIGNAL_H
# define LIBC_COMPAT_SIGNAL_H


# if defined(__linux__)
#  include "kernel/linux/signal.h"
# elif defined(__NetBSD__)
#  include "kernel/netbsd/signal.h"
# else
#  warning Unsupported platform
# endif

#endif /* !LIBC_COMPAT_SIGNAL_H */
