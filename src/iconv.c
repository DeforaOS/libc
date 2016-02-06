/* $Id$ */
/* Copyright (c) 2008-2016 Pierre Pronchery <khorben@defora.org> */
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
#include "string.h"
#include "strings.h"
#include "errno.h"
#include "iconv.h"


/* types */
typedef enum _iconv_code
{
	IC_UNKNOWN = -1,
	IC_ISO_8859_1,
	IC_ISO_8859_15,
	IC_UTF_8
} iconv_code;


/* constants */
static struct
{
	iconv_code code;
	char const * name;
} _iconv_names[] =
{
	{ IC_ISO_8859_1, "iso-8859-1" },
	{ IC_ISO_8859_15, "iso-8859-15" },
	{ IC_UTF_8, "UTF-8" },
	{ IC_UTF_8, "UTF8" }
};


/* functions */
/* iconv_open */
static iconv_code _open_code(char const * code);

iconv_t iconv_open(const char * tocode, const char * fromcode)
{
	iconv_t cd;
	iconv_code code;

	if((code = _open_code(tocode)) == IC_UNKNOWN)
	{
		errno = EINVAL;
		return (iconv_t)-1;
	}
	cd = code;
	if((code = _open_code(fromcode)) == IC_UNKNOWN)
	{
		errno = EINVAL;
		return (iconv_t)-1;
	}
	cd |= code << 16;
	return cd;
}

static iconv_code _open_code(char const * code)
{
	size_t i;

	for(i = 0; i < sizeof(_iconv_names) / sizeof(*_iconv_names); i++)
		if(strcasecmp(_iconv_names[i].name, code) == 0)
			return _iconv_names[i].code;
	return IC_UNKNOWN;
}


/* iconv */
size_t iconv(iconv_t cd, char ** inbuf, size_t * inbytesleft, 
		char ** outbuf, size_t * outbytesleft)
{
	if((cd & 0xffff) == ((cd >> 16) & 0xffff))
	{
		/* no conversion is required */
		if(*inbytesleft > *outbytesleft)
		{
			/* the conversion will not fit */
			errno = E2BIG;
			return (size_t)-1;
		}
		memcpy(*outbuf, *inbuf, *inbytesleft);
		(*inbuf) += *inbytesleft;
		(*outbuf) += *inbytesleft;
		(*outbytesleft) -= *inbytesleft;
		*inbytesleft = 0;
		return 0;
	}
	errno = ENOSYS;
	return (size_t)-1;
}


/* iconv_close */
int iconv_close(iconv_t cd)
{
	(void) cd;

	return 0;
}
