/* $Id$ */
/* Copyright (c) 2008 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_WCHAR_H
# define LIBC_WCHAR_H


/* types */
/* FIXME check if size_t and wchar_t are correct */
# ifndef FILE
#  define FILE FILE
typedef struct _FILE FILE;
# endif
# ifndef size_t
#  define size_t size_t
typedef unsigned int size_t;
# endif
# ifndef wchar_t
#  define wchar_t wchar_t
typedef char wchar_t;
# endif


/* constants */
# ifndef NULL
#  define NULL ((void*)0)
# endif

#endif /* !LIBC_WCHAR_H */
