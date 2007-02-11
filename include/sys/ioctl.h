/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_SYS_IOCTL_H
# define LIBC_SYS_IOCTL_H

# include "compat/sys/ioctl.h"


/* functions */
int ioctl(int fildes, int request, ...);

#endif /* !LIBC_SYS_IOCTL_H */
