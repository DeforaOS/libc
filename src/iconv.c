/* $Id$ */
/* Copyright (c) 2008-2012 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */



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
		free(cd->fromcode);
		free(cd->tocode);
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
