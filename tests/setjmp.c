/* $Id$ */
/* Copyright (c) 2012 Pierre Pronchery <khorben@defora.org> */
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
		memset(_jb, 0, sizeof(jmp_buf));
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
		memset(_sjb, 0, sizeof(sigjmp_buf));
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
