/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_KERNEL_NETBSD_SYS_MMAN_H
# define LIBC_KERNEL_NETBSD_SYS_MMAN_H


/* constants */
# define PROT_READ	0x1
# define PROT_WRITE	0x2
# define PROT_EXEC	0x4
# define PROT_NONE	0x0

# define MAP_SHARED	0x01
# define MAP_PRIVATE	0x02
# define MAP_FIXED	0x10
# define MAP_ANONYMOUS	0x100

#endif /* !LIBC_KERNEL_NETBSD_SYS_MMAN_H */
