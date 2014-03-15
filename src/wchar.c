/* $Id$ */
/* Copyright (c) 2013 Pierre Pronchery <khorben@defora.org> */
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



#include "errno.h"
#include "wchar.h"


/* public */
/* functions */
size_t mbrtowc(wchar_t * pwc, const char * s, size_t n, mbstate_t * ps)
{
	/* FIXME implement */
	errno = ENOSYS;
	return (size_t)-1;
}


/* mbstowcs */
size_t mbstowcs(wchar_t * pwcs, const char * s, size_t n)
{
	/* FIXME implement */
	errno = ENOSYS;
	return (size_t)-1;
}


/* mbtowc */
int mbtowc(wchar_t * pwc, const char * s, size_t n)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}