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



#ifndef LIBC_KERNEL_NETBSD_UNISTD_H
# define LIBC_KERNEL_NETBSD_UNISTD_H


/* types */
# ifndef off_t
#  define off_t off_t
typedef long long off_t;
# endif
# ifndef useconds_t
#  define useconds_t useconds_t
typedef unsigned int useconds_t;
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

# define _SC_OPEN_MAX	5
# define _SC_PAGESIZE	28
# define _SC_CLK_TCK	39

#endif /* !LIBC_KERNEL_NETBSD_UNISTD_H */
