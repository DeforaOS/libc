/* $Id$ */
/* Copyright (c) 2016 Pierre Pronchery <khorben@defora.org> */
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



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iconv.h>


/* private */
/* prototypes */
static int _iconv(char const * progname, char const * tocode,
		char const * fromcode, char const * buf, char const * expected);
static int _iconv_error(char const * message, int ret);


/* functions */
/* iconv */
static int _iconv(char const * progname, char const * tocode,
		char const * fromcode, char const * buf, char const * expected)
{
	int ret;
	iconv_t cd;
	size_t inbytesleft;
	char * outbuf;
	char * p;
	size_t outbytesleft;

	printf("%s: Testing %s: \"%s\" to \"%s\"\n", progname, "iconv()",
			fromcode, tocode);
	inbytesleft = strlen(buf);
	if((outbuf = malloc(inbytesleft + 1)) == NULL)
		return _iconv_error(NULL, 1);
	p = outbuf;
	outbuf[inbytesleft] = '\0';
	if((cd = iconv_open(tocode, fromcode)) == (iconv_t)-1)
	{
		free(outbuf);
		return _iconv_error(NULL, 2);
	}
	if((ret = iconv(cd, &buf, &inbytesleft, &p, &outbytesleft)) == 0
			&& strcmp(outbuf, expected) != 0)
		ret = _iconv_error(NULL, 3);
	iconv_close(cd);
	free(outbuf);
	return ret;
}


/* iconv_error */
static int _iconv_error(char const * message, int ret)
{
	fputs("iconv: ", stderr);
	perror(message);
	return ret;
}


/* public */
/* functions */
/* main */
int main(int argc, char * argv[])
{
	int ret;
	(void) argc;

	ret = _iconv(argv[0], "ISO-8859-1", "ISO-8859-1", "", "");
	ret |= _iconv(argv[0], "ISO-8859-15", "iso-8859-15", "test", "test");
	ret |= _iconv(argv[0], "UTF-8", "UTF8", "test", "test");
	ret |= _iconv(argv[0], "UTF-8", "UTF-8", "test", "test");
	return (ret == 0) ? 0 : 2;
}
