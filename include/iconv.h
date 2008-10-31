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



#ifndef LIBC_ICONV_H
# define LIBC_ICONV_H


/* types */
typedef struct _iconv_t * iconv_t;


/* functions */
iconv_t iconv_open(const char * tocode, const char * fromcode);
size_t iconv(iconv_t cd, char ** inbuf, size_t * inbytesleft,
		char ** outbuf, size_t * outbytesleft);
int iconv_close(iconv_t cd);

#endif /* !LIBC_ICONV_H */
