/* $Id$ */
/* Copyright (c) 2012-2017 Pierre Pronchery <khorben@defora.org> */
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



#include <stdint.h>
#include <stdio.h>


/* stdint */
static int _stdint(char const * progname, size_t size, char const * name,
		size_t expected)
{
	int ret = 0;
	char const * message = "";

	if(size != expected)
	{
		ret = 1;
		message = "FAILED";
	}
	printf("%s: Testing %s: %u (%u)%s\n", progname, name, size, expected,
			message);
	return ret;
}


/* main */
int main(int argc, char * argv[])
{
	int ret = 0;
	(void) argc;

	ret |= _stdint(argv[0], sizeof(int8_t), "int8_t", 1);
	ret |= _stdint(argv[0], sizeof(int16_t), "int16_t", 2);
	ret |= _stdint(argv[0], sizeof(int32_t), "int32_t", 4);
	ret |= _stdint(argv[0], sizeof(int64_t), "int64_t", 8);
	ret |= _stdint(argv[0], sizeof(uint8_t), "uint8_t", 1);
	ret |= _stdint(argv[0], sizeof(uint16_t), "uint16_t", 2);
	ret |= _stdint(argv[0], sizeof(uint32_t), "uint32_t", 4);
	ret |= _stdint(argv[0], sizeof(uint64_t), "uint64_t", 8);
	return (ret == 0) ? 0 : 2;
}
