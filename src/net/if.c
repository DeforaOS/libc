/* $Id$ */
/* Copyright (c) 2011 Pierre Pronchery <khorben@defora.org> */
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



#include "stddef.h"
#include "errno.h"
#include "net/if.h"


/* public */
/* functions */
/* if_nametoindex */
unsigned int if_nametoindex(const char * name)
{
	/* FIXME implement */
	return 0;
}


/* if_indextoname */
char * if_indextoname(unsigned int index, char * name)
{
	/* FIXME implement */
	errno = ENOSYS;
	return NULL;
}


/* if_nameindex */
struct if_nameindex * if_nameindex(void)
{
	/* FIXME implement */
	errno = ENOSYS;
	return NULL;
}


/* if_freenameindex */
void if_freenameindex(struct if_nameindex * nameindex)
{
	/* FIXME implement */
}
