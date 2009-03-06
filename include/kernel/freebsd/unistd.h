/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_KERNEL_FREEBSD_UNISTD_H
# define LIBC_KERNEL_FREEBSD_UNISTD_H


/* types */
# ifndef off_t
#  define off_t off_t
typedef long long off_t;
# endif
# ifndef useconds_t
#  define useconds_t useconds_t
typedef unsigned long useconds_t;
# endif


/* constants */
# ifndef SEEK_SET
#  define SEEK_SET	0
# endif
# ifndef SEEK_CUR
#  define SEEK_CUR	1
# endif
# ifndef SEEK_END
#  define SEEK_END	2
# endif

# define _SC_CLK_TCK	3
# define _SC_PAGESIZE	47

#endif /* !LIBC_KERNEL_FREEBSD_UNISTD_H */
