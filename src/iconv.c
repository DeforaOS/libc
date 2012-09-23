/* $Id$ */
/* Copyright (c) 2008-2012 Pierre Pronchery <khorben@defora.org> */
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



#include "sys/types.h"
#include "stdlib.h"
#include "string.h"
#include "errno.h"
#include "iconv.h"


/* types */
struct _iconv_t
{
	char * tocode;
	char * fromcode;
};


/* functions */
/* iconv_open */
iconv_t iconv_open(const char * tocode, const char * fromcode)
{
	iconv_t cd;

	if((cd = malloc(sizeof(*cd))) == NULL)
		return NULL;
	cd->tocode = strdup(tocode);
	cd->fromcode = strdup(fromcode);
	if(cd->tocode == NULL || cd->fromcode == NULL)
	{
		free(cd);
		return NULL;
	}
	return cd;
}


/* iconv */
size_t iconv(iconv_t cd, char ** inbuf, size_t * inbytesleft, 
		char ** outbuf, size_t * outbytesleft)
{
	errno = ENOSYS;
	return (size_t)-1;
}


/* iconv_close */
int iconv_close(iconv_t cd)
{
	free(cd->tocode);
	free(cd->fromcode);
	free(cd);
	return 0;
}
