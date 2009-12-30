/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. */



#ifndef LIBC_KERNEL_OPENBSD_SYS_TYPES_H
# define LIBC_KERNEL_OPENBSD_SYS_TYPES_H


/* types */
# ifndef blkcnt_t
#  define blkcnt_t blkcnt_t
typedef unsigned long long blkcnt_t;
# endif
# ifndef clock_t
#  define clock_t clock_t
typedef unsigned int clock_t;
# endif
# ifndef dev_t
#  define dev_t dev_t
typedef unsigned int dev_t;
# endif
# ifndef fsblkcnt_t
#  define fsblkcnt_t fsblkcnt_t
typedef unsigned int fsblkcnt_t;
# endif
# ifndef fsfilcnt_t
#  define fsfilcnt_t fsfilcnt_t
typedef unsigned int fsfilcnt_t;
# endif
# ifndef off_t
#  define off_t off_t
typedef long long off_t;
# endif
# ifndef suseconds_t
#  define suseconds_t suseconds_t
typedef int suseconds_t;
# endif
# ifndef time_t
#  define time_t time_t
typedef int time_t;
# endif
# ifndef useconds_t
#  define useconds_t useconds_t
typedef unsigned int useconds_t;
# endif

#endif /* !LIBC_KERNEL_OPENBSD_SYS_TYPES_H */
