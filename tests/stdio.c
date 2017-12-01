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



#include <fcntl.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../src/stdio.c"


/* stdio */
/* fmemopen */
static int _fmemopen(char const * progname, void * buffer, size_t size)
{
	int ret = 1;
	FILE * file;
	char * buf;
	size_t s;

	printf("%s: Testing fmemopen()\n", progname);
	if((file = fmemopen(buffer, size, "r")) == NULL)
		return 2;
	if((buf = malloc(size)) == NULL)
	{
		fclose(file);
		return 3;
	}
	if((s = fread(buf, sizeof(*buf), size, file)) != size)
		printf("%s: Obtained %lu (expected: %lu)\n", progname, s, size);
	else if(memcmp(buf, buffer, size) != 0)
		printf("%s: Obtained \"%s\" (expected: \"%s\")\n", progname,
				buf, buffer);
	else
		ret = 0;
	free(buf);
	if(fclose(file) != 0 && ret == 0)
		ret = 4;
	return ret;
}


/* fopen */
static int _fopen(char const * progname, char const * mode, int expected)
{
	int m = _fopen_mode(mode);

	printf("%s: Testing fopen() mode \"%s\": 0x%x (0x%x)\n", progname,
			mode, m, expected);
	return (m == expected) ? 0 : 1;
}


/* printf */
static int _printf(char const * progname, char const * format, int64_t i,
		char const * expected)
{
	int ret;
	char * buf;
	int len;

	printf("%s: Testing printf(\"%s\")\n", progname, format);
	if((len = snprintf(NULL, 0, format, i)) <= 0)
		return -1;
	if((buf = malloc(len + 2)) == NULL)
		return -1;
	snprintf(buf, len + 2, format, i);
	buf[len + 1] = '\0';
	if((ret = strcmp(buf, expected)) != 0)
		printf("%s: Obtained \"%s\" (expected: \"%s\")\n", progname,
				buf, expected);
	free(buf);
	return ret;
}


/* sscanf */
static int _sscanf(char const * progname)
{
	char const * str = "abc   e 42def3";
	char const * format = "abc e %udef%c";
	unsigned int u;
	char c;
	char buf[4];

	printf("%s: Testing sscanf()\n", progname);
	if(sscanf(str, format, &u, &c) != 2
			|| u != 42 || c != '3')
		return 1;
	if(sscanf(str, "a%3s", &buf) != 1
			|| strncmp(&str[1], buf, 2) != 0)
		return 2;
	if(sscanf(str, "a%3c", &buf) != 1
			|| strncmp(&str[1], buf, 3) != 0)
		return 3;
	return 0;
}


/* tmpfile */
static int _tmpfile(char const * progname)
{
	FILE * fp;

	printf("%s: Testing tmpfile()\n", progname);
	if((fp = tmpfile()) == NULL)
		return 1;
	fclose(fp);
	return 0;
}


/* tmpnam */
static int _tmpnam(char const * progname, char * str)
{
	printf("%s: Testing tmpnam()\n", progname);
	return (tmpnam(str) != NULL) ? 0 : 1;
}


/* main */
int main(int argc, char * argv[])
{
	int ret = 0;
	(void) argc;

	ret += _fmemopen(argv[0], "test", 5);
	ret += _fopen(argv[0], "a", O_WRONLY | O_APPEND | O_CREAT);
	ret += _fopen(argv[0], "ab", O_WRONLY | O_APPEND | O_CREAT);
	ret += _fopen(argv[0], "a+", O_RDWR | O_APPEND | O_CREAT);
	ret += _fopen(argv[0], "ab+", O_RDWR | O_APPEND | O_CREAT);
	ret += _fopen(argv[0], "ax", O_WRONLY | O_APPEND | O_CREAT | O_EXCL);
	ret += _fopen(argv[0], "abx", O_WRONLY | O_APPEND | O_CREAT | O_EXCL);
	ret += _fopen(argv[0], "a+x", O_RDWR | O_APPEND | O_CREAT | O_EXCL);
	ret += _fopen(argv[0], "ab+x", O_RDWR | O_APPEND | O_CREAT | O_EXCL);
	ret += _fopen(argv[0], "r", O_RDONLY);
	ret += _fopen(argv[0], "rb", O_RDONLY);
	ret += _fopen(argv[0], "r+", O_RDWR);
	ret += _fopen(argv[0], "rb+", O_RDWR);
	ret += _fopen(argv[0], "rx", O_RDONLY | O_EXCL);
	ret += _fopen(argv[0], "rbx", O_RDONLY | O_EXCL);
	ret += _fopen(argv[0], "r+x", O_RDWR | O_EXCL);
	ret += _fopen(argv[0], "rb+x", O_RDWR | O_EXCL);
	ret += _fopen(argv[0], "w", O_WRONLY | O_TRUNC | O_CREAT);
	ret += _fopen(argv[0], "wb", O_WRONLY | O_TRUNC | O_CREAT);
	ret += _fopen(argv[0], "w+", O_RDWR | O_TRUNC | O_CREAT);
	ret += _fopen(argv[0], "wb+", O_RDWR | O_TRUNC | O_CREAT);
	ret += _fopen(argv[0], "wx", O_WRONLY | O_TRUNC | O_CREAT | O_EXCL);
	ret += _fopen(argv[0], "wbx", O_WRONLY | O_TRUNC | O_CREAT | O_EXCL);
	ret += _fopen(argv[0], "w+x", O_RDWR | O_TRUNC | O_CREAT | O_EXCL);
	ret += _fopen(argv[0], "wb+x", O_RDWR | O_TRUNC | O_CREAT | O_EXCL);
	ret += _printf(argv[0], "%d", 42, "42");
	ret += _printf(argv[0], "%3d", 42, " 42");
	ret += _printf(argv[0], "%d", -42, "-42");
	ret += _printf(argv[0], "%4d", -42, " -42");
	ret += _printf(argv[0], "%o", 42, "52");
	ret += _printf(argv[0], "%u", 42, "42");
	ret += _printf(argv[0], "%x", 42, "2a");
	ret += _printf(argv[0], "%#x", 42, "0x2a");
	ret += _printf(argv[0], "%X", 42, "2A");
	ret += _sscanf(argv[0]);
	ret += _tmpfile(argv[0]);
	ret += _tmpnam(argv[0], NULL);
	return (ret == 0) ? 0 : 2;
}
