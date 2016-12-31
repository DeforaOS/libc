/* $Id$ */
/* Copyright (c) 2012-2016 Pierre Pronchery <khorben@defora.org> */
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



#include <setjmp.h>
#include <stdio.h>
#include <string.h>


/* setjmp */
/* private */
/* variables */
static jmp_buf _jb;
static sigjmp_buf _sjb;
static int _ret;


/* prototypes */
#ifdef DEBUG
static void _jmp_buf_dump(jmp_buf jb);
static void _sigjmp_buf_dump(sigjmp_buf jb);
#endif

/* _setjmp */
static void __setjmp_test1(void);
static void __setjmp_test2(void);

/* setjmp */
static void _setjmp_test1(void);
static void _setjmp_test2(void);

/* sigsetjmp */
static void _sigsetjmp_test1(void);
static void _sigsetjmp_test2(void);


/* functions */
#ifdef DEBUG
/* jmp_buf_dump */
static void _jmp_buf_dump(jmp_buf jb)
{
	size_t i;
	char const * sep = "";

	fprintf(stderr, "DEBUG: %s()\n", __func__);
	for(i = 0; i < sizeof(jmp_buf) / sizeof(*jb); i++)
	{
		fprintf(stderr, "%s%p", sep, jb[i]);
		sep = " ";
	}
	fputs("\n", stderr);
}


/* sigjmp_buf_dump */
static void _sigjmp_buf_dump(sigjmp_buf sjb)
{
	size_t i;
	char const * sep = "";

	fprintf(stderr, "DEBUG: %s()\n", __func__);
	for(i = 0; i < sizeof(sigjmp_buf) / sizeof(*sjb); i++)
	{
		fprintf(stderr, "%s%p", sep, sjb[i]);
		sep = " ";
	}
	fputs("\n", stderr);
}
#endif


/* _setjmp */
/* _setjmp_test1 */
static void __setjmp_test1(void)
{
#ifdef DEBUG
	fprintf(stderr, "DEBUG: %s()\n", __func__);
#endif
	_ret = 3;
	__setjmp_test2();
}


/* _setjmp_test2 */
static void __setjmp_test2(void)
{
#ifdef DEBUG
	fprintf(stderr, "DEBUG: %s()\n", __func__);
#endif
	_ret = 4;
	_longjmp(_jb, 5);
	_ret = 6;
}


/* setjmp */
/* setjmp_test1 */
static void _setjmp_test1(void)
{
#ifdef DEBUG
	fprintf(stderr, "DEBUG: %s()\n", __func__);
#endif
	_ret = 3 << 1;
	_setjmp_test2();
}


/* setjmp_test2 */
static void _setjmp_test2(void)
{
#ifdef DEBUG
	fprintf(stderr, "DEBUG: %s()\n", __func__);
#endif
	_ret = 4 << 1;
	longjmp(_jb, 5 << 1);
	_ret = 6 << 1;
}


/* sigsetjmp */
/* sigsetjmp_test1 */
static void _sigsetjmp_test1(void)
{
#ifdef DEBUG
	fprintf(stderr, "DEBUG: %s()\n", __func__);
#endif
	_ret = 3 << 2;
	_sigsetjmp_test2();
}


/* sigsetjmp_test2 */
static void _sigsetjmp_test2(void)
{
#ifdef DEBUG
	fprintf(stderr, "DEBUG: %s()\n", __func__);
#endif
	_ret = 4 << 2;
	siglongjmp(_sjb, (5 << 2));
	_ret = 6 << 2;
}


/* public */
/* functions */
/* main */
int main(int argc, char * argv[])
{
	int res;

	/* _setjmp */
	printf("%s: %s", argv[0], "Testing _setjmp()\n");
	_ret = 2;
	if((res = _setjmp(_jb)) == 0)
	{
#ifdef DEBUG
		_jmp_buf_dump(_jb);
#endif
		__setjmp_test1();
	}
	else if(res == 5)
		_ret = 0;
	else
		fprintf(stderr, "%s: %s", argv[0], "_setjmp() failed\n");
	/* setjmp */
	if(_ret == 0)
	{
		printf("%s: %s", argv[0], "Testing setjmp()\n");
		_ret = 2;
		memset(&_jb, 0, sizeof(_jb));
		if((res = setjmp(_jb)) == 0)
		{
#ifdef DEBUG
			_jmp_buf_dump(_jb);
#endif
			_setjmp_test1();
		}
		else if(res == (5 << 1))
			_ret = 0;
		else
			fprintf(stderr, "%s: %s", argv[0], "setjmp() failed\n");
	}
	/* sigsetjmp (not saving the signal mask) */
	if(_ret == 0)
	{
		printf("%s: %s", argv[0], "Testing sigsetjmp(1/2)\n");
		_ret = 2;
		if((res = sigsetjmp(_sjb, 0)) == 0)
		{
#ifdef DEBUG
			_sigjmp_buf_dump(_sjb);
#endif
			_sigsetjmp_test1();
		}
		else if(res == (5 << 2))
			_ret = 0;
		else
			fprintf(stderr, "%s: %s", argv[0],
					"sigsetjmp(1/2) failed\n");
	}
	/* sigsetjmp (saving the signal mask) */
	if(_ret == 0)
	{
		printf("%s: %s", argv[0], "Testing sigsetjmp(2/2)\n");
		_ret = 2;
		memset(&_sjb, 0, sizeof(_sjb));
		if((res = sigsetjmp(_sjb, (5 << 2))) == 0)
		{
#ifdef DEBUG
			_sigjmp_buf_dump(_sjb);
#endif
			_sigsetjmp_test1();
		}
		else if(res == (5 << 2))
			_ret = 0;
		else
			fprintf(stderr, "%s: %s", argv[0],
					"sigsetjmp(2/2) failed\n");
	}
	return _ret;
}
