/* $Id$ */
/* Copyright (c) 2008 Pierre Pronchery <khorben@defora.org> */
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
