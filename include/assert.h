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



#ifndef LIBC_ASSERT_H
# define LIBC_ASSERT_H


# ifdef NDEBUG
#  define assert(ignore) ((void)0)
# else
#  include <stdio.h>
#  define assert(value) if(!(value)) { fprintf(stderr, "%s%s%s%d%s", \
			"assertion failed in \"", __FILE__, "\", line ", \
			__LINE__, "\n"); }
# endif

#endif /* !LIBC_ASSERT_H */
