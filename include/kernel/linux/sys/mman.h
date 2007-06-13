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



#ifndef LIBC_KERNEL_LINUX_SYS_MMAN_H
# define LIBC_KERNEL_LINUX_SYS_MMAN_H


/* types */
# ifndef off_t
#  define off_t off_t
typedef long long off_t;
# endif


/* constants */
# define PROT_READ	0x1
# define PROT_WRITE	0x2
# define PROT_EXEC	0x4
# define PROT_NONE	0x0

# define MAP_SHARED	0x01
# define MAP_PRIVATE	0x02
# define MAP_FIXED	0x10
# define MAP_ANONYMOUS	0x20

#endif /* !LIBC_KERNEL_LINUX_SYS_MMAN_H */
