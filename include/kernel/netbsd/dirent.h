/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_KERNEL_NETBSD_DIRENT_H
# define LIBC_KERNEL_NETBSD_DIRENT_H


/* types */
# ifndef ino_t
#  define ino_t ino_t
typedef unsigned int ino_t;
# endif

struct dirent
{
	ino_t d_ino;
	unsigned short int d_reclen;
	unsigned char d_type;
	unsigned char d_namlen;
	char d_name[256]; /* NAME_MAX + 1 */
};

#endif /* !LIBC_KERNEL_NETBSD_DIRENT_H */
