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



#ifndef LIBC_NET_IF_H
# define LIBC_NET_IF_H


/* types */
# ifndef if_nameindex
#  define if_nameindex if_nameindex
struct if_nameindex
{
	unsigned if_index;
	char * if_name;
};
# endif


/* functions */
unsigned if_nametoindex(const char *);
char * if_indextoname(unsigned, char *);
struct if_nameindex * if_nameindex(void);
void if_freenameindex(struct if_nameindex *);

#endif
