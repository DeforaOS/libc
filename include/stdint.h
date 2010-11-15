/* $Id$ */
/* Copyright (c) 2010 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_STDINT_H
# define LIBC_STDINT_H


/* types */
typedef char int8_t;
typedef short int int16_t;
typedef int int32_t;
typedef long long int64_t;
typedef unsigned char uint8_t;
#ifndef uint16_t
# define uint16_t uint16_t
typedef unsigned short uint16_t;
#endif
#ifndef uint32_t
# define uint32_t uint32_t
typedef unsigned int uint32_t;
#endif
typedef unsigned long long uint64_t;

# ifndef intmax_t
#  define intmax_t intmax_t
typedef long intmax_t;
# endif
# ifndef intptr_t
#  define intptr_t intptr_t
typedef signed long intptr_t;
# endif
# ifndef uintmax_t
#  define uintmax_t uintmax_t
typedef unsigned long uintmax_t;
# endif
# ifndef uintptr_t
#  define uintptr_t uintptr_t
typedef unsigned long uintptr_t;
# endif

#endif /* !LIBC_STDINT_H */
