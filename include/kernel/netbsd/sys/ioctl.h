/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_KERNEL_NETBSD_SYS_IOCTL_H
# define LIBC_KERNEL_NETBSD_SYS_IOCTL_H


/* macros */
# define _IOC(inout, group, num, len) \
	(inout | ((len & IOCPARM_MASK) << 16) | ((group) << 8) | (num))
# define _IOR(g, n, t) _IOC(IOC_OUT, (g), (n), sizeof(t))


/* constants */
# define IOCPARM_MASK	0x1fff
# define IOC_OUT	(unsigned long)0x40000000
# define IOC_DIRMASK	(unsigned long)0xe0000000

# define TIOCGETA _IOR('t', 19, struct termios)

#endif /* !LIBC_KERNEL_NETBSD_SYS_IOCTL_H */
