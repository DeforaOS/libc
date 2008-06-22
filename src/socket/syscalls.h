/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#ifndef LIBSOCKET_SYSCALLS_H
# define LIBSOCKET_SYSCALLS_H

# if defined(__linux__)
#  include "../kernel/linux/socket.h"
# elif defined(__NetBSD__)
#  include "../kernel/netbsd/socket.h"
# else
#  warning Unsupported platform
# endif

#endif /* !LIBSOCKET_SYSCALLS_H */
