/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_KERNEL_LINUX_DIRENT_H
# define LIBC_KERNEL_LINUX_DIRENT_H


/* types */
# ifndef off_t
#  define off_t off_t
typedef int off_t;
# endif

struct dirent
{
	ino_t d_ino;
	off_t d_off;
	unsigned short int d_reclen;
	unsigned char d_type;
	char d_name[256]; /* NAME_MAX + 1 */
};

#endif /* !LIBC_KERNEL_LINUX_DIRENT_H */
