/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#ifndef SOCKET_SYSCALLS_H
# define SOCKET_SYSCALLS_H

# if defined(__NetBSD__)
#  include "../kernel/netbsd/socket.h"
# else
#  warning Unsupported platform
# endif

#endif /* !SOCKET_SYSCALLS_H */
