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



#ifndef LIBC_KERNEL_NETBSD_SYS_MMAN_H
# define LIBC_KERNEL_NETBSD_SYS_MMAN_H


/* types */
# ifndef off_t
#  define off_t off_t
typedef long long off_t;
# endif


/* constants */
# define PROT_NONE	0x0
# define PROT_READ	0x1
# define PROT_WRITE	0x2
# define PROT_EXEC	0x4

# define MAP_SHARED	0x0001
# define MAP_PRIVATE	0x0002
# define MAP_FIXED	0x0010
# define MAP_ANONYMOUS	0x1000

#endif /* !LIBC_KERNEL_NETBSD_SYS_MMAN_H */
