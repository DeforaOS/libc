/* $Id$ */
/* Copyright (c) 2007 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* libc is not free software; you can redistribute it and/or modify it under
 * the terms of the Creative Commons Attribution-NonCommercial-ShareAlike 3.0
 * Unported as published by the Creative Commons organization.
 *
 * libc is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the Creative Commons Attribution-NonCommercial-
 * ShareAlike 3.0 Unported license for more details.
 *
 * You should have received a copy of the Creative Commons Attribution-
 * NonCommercial-ShareAlike 3.0 along with libc; if not, browse to
 * http://creativecommons.org/licenses/by-nc-sa/3.0/ */



#ifndef LIBC_KERNEL_LINUX_DIRENT_H
# define LIBC_KERNEL_LINUX_DIRENT_H


/* types */
# ifndef ino_t
#  define ino_t ino_t
typedef unsigned long long ino_t;
# endif
# ifndef off_t
#  define off_t off_t
typedef long long off_t;
# endif

# pragma pack(1)
struct dirent
{
# ifdef __arm__
	unsigned long d_ino;
	unsigned long d_off;
	unsigned char d_reclen;
	unsigned char d_type;
	char d_name[256]; /* NAME_MAX + 1 */
# else
	ino_t d_ino;
	off_t _padding;
	unsigned short d_reclen;
	unsigned char d_type;
	char d_name[256]; /* NAME_MAX + 1 */
# endif
};
# pragma pack()

#endif /* !LIBC_KERNEL_LINUX_DIRENT_H */
