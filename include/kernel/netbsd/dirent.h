/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_KERNEL_NETBSD_DIRENT_H
# define LIBC_KERNEL_NETBSD_DIRENT_H

# include <stdint.h> /* XXX */


/* types */
struct dirent
{
	uint32_t d_fileno;
	uint16_t d_reclen;
	uint8_t d_type;
	uint8_t d_namlen;
	char d_name[256]; /* NAME_MAX + 1 */
};

#endif /* !LIBC_KERNEL_NETBSD_DIRENT_H */
