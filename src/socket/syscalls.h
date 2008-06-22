/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#ifndef LIBSOCKET_SYSCALLS_H
# define LIBSOCKET_SYSCALLS_H

# if defined(__linux__)
#  include "kernel/linux/common.h"
# elif defined(__NetBSD__)
#  include "kernel/netbsd/common.h"
# else
#  warning Unsupported platform
# endif

#endif /* !LIBSOCKET_SYSCALLS_H */
