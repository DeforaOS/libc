/* $Id$ */
/* Copyright (c) 2014-2025 Pierre Pronchery <khorben@defora.org> */
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



#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>

extern char ** environ;


/* stdlib */
/* private */
/* prototypes */
static int _error(char const * progname, char const * message, int ret);

static int _arc4random(char const * progname);
static int _calloc(char const * progname);
static int _environ(char const * program);
static int _mkstemp(char const * progname);
static int _mktemp(char const * progname);
static int _rand(char const * progname);
static int _strtold(char const * progname, char const * str,
		long double expected);
static int _strtol(char const * progname);
static int _strtoll(char const * progname);
static int _strtoul(char const * progname);
static int _strtoull(char const * progname);


/* functions */
/* arc4random */
static int _arc4random(char const * progname)
{
	uint32_t res[4];
	size_t i;

	printf("%s: Testing arc4random()\n", progname);
	/* XXX not deterministic */
	for(i = 0; i < sizeof(res) / sizeof(*res); i++)
		res[i] = arc4random();
	for(i = 0; i < sizeof(res) / sizeof(*res); i++)
		printf("%u. 0x%08x\n", i + 1, res[i]);
	/* XXX false negatives are unlikely but possible */
	if(res[0] == res[1] && res[0] == res[2] && res[0] == res[3])
		return 1;
	return 0;
}


/* calloc */
static int _calloc(char const * progname)
{
	int * p;
	size_t i;
	const size_t cnt = 16;

	printf("%s: Testing calloc()\n", progname);
	if(calloc(SIZE_MAX, 2) != NULL || calloc(2, SIZE_MAX) != NULL)
	{
		printf("calloc() failed to detect overflow\n");
		return 1;
	}
	if((p = calloc(sizeof(int), cnt)) == NULL)
	{
		printf("calloc() failed to allocate memory\n");
		return 1;
	}
	for(i = 0; i < cnt; i++)
		if(p[i] != 0)
		{
			printf("calloc() failed to clear memory\n");
			return 1;
		}
	free(p);
	return 0;
}


/* environ */
static int _environ(char const * progname)
{
	char ** e;

	printf("%s: Testing environ\n", progname);
	for(e = environ; *e != NULL; e++)
		printf("%s: %s\n", progname, *e);
	return 0;
}


/* error */
static int _error(char const * progname, char const * message, int ret)
{
	fputs(progname, stderr);
	fputs(": ", stderr);
	perror(message);
	return ret;
}


/* mkstemp */
static int _mkstemp(char const * progname)
{
	int ret = 0;
	char buf[] = "/tmp/stdlib.XXXXXX";
	int fd;

	printf("%s: Testing mkstemp()\n", progname);
	if((fd = mkstemp(buf)) < 0)
		return _error(progname, "mkstemp", 1);
	if(unlink(buf) != 0)
		ret = _error(progname, "unlink", 1);
	if(close(fd) != 0)
		ret = _error(progname, "close", 1);
	return ret;
}


/* mktemp */
static int _mktemp(char const * progname)
{
	char buf[] = "/tmp/stdlib.XXXXXX";

	printf("%s: Testing mktemp()\n", progname);
	return (mktemp(buf) == buf) ? 0 : _error(progname, "mktemp", 1);
}


/* rand */
static int _rand_test(unsigned int seed, const uint16_t * expected,
		const unsigned int cnt);

static int _rand(char const * progname)
{
	int ret = 0;
	const uint16_t expected1[10] = { 19533, 24984, 3136, 4047, 27914, 25471,
		17373, 7887, 7782, 20541 };
	const uint16_t expected0[10] = { 30440, 896, 24647, 22198, 11946, 311,
		28109, 32562, 13591, 7962 };

	printf("%s: Testing rand()\n", progname);
	if(_rand_test(1, expected1, sizeof(expected1) / sizeof(*expected1)) != 0
			|| _rand_test(0, expected0,
				sizeof(expected0) / sizeof(*expected0)) != 0)
	{
		errno = ERANGE;
		ret = _error(progname, "srand", 1);
	}
	return ret;
}

static int _rand_test(unsigned int seed, const uint16_t * expected,
		const unsigned int cnt)
{
	int ret = 0;
	unsigned int i;
	uint16_t obtained;

	srand(seed);
	for(i = 0; i < cnt; i++)
	{
		obtained = rand();
		printf("%u:%u: %u (%u)\n", seed, i, obtained, expected[i]);
		if(obtained != expected[i])
			ret = 1;
	}
	return ret;
}


/* realloc */
static int _realloc(char const * progname)
{
	size_t i;
	char * p = NULL;
	char * q;

	printf("%s: Testing realloc()\n", progname);
	for(i = 0; i < 65536; i++)
	{
		if((q = realloc(p, arc4random() % 65536)) == NULL)
		{
			fprintf(stderr, "%s: %s: %s (%zu)\n", progname,
					"realloc", strerror(errno), i);
			free(p);
			return -1;
		}
		p = q;
	}
	free(p);
	return 0;
}


/* strtold */
static int _strtold(char const * progname, char const * str,
		long double expected)
{
	int ret = 0;
	long double ld;
	double d;
	float f;
	char * p;

	printf("%s: Testing strtold(\"%s\", %Lf)\n", progname, str, expected);
	ld = strtold(str, &p);
	if(ld != expected || *p != '\0')
	{
		fprintf(stderr, "%s: %s: Obtained %Lf (expected: %Lf)\n",
				progname, "strtold", ld, expected);
		ret = 1;
	}
	printf("%s: Testing strtod(\"%s\", %Lf)\n", progname, str, expected);
	d = strtod(str, &p);
	if(d != (double)expected || *p != '\0')
	{
		fprintf(stderr, "%s: %s: Obtained %f (expected: %f)\n",
				progname, "strtod", d, expected);
		ret = 1;
	}
	printf("%s: Testing strtof(\"%s\", %Lf)\n", progname, str, expected);
	f = strtof(str, &p);
	if(f != (float)expected || *p != '\0')
	{
		fprintf(stderr, "%s: %s: Obtained %f (expected: %f)\n",
				progname, "strtof", f, expected);
		ret = 1;
	}
	return ret;
}


/* strtol */
static int _strtol(char const * progname)
{
	char * p;
	char const spaces[] = "      ";
	long l;
	unsigned long lu;
	char buf[32];

	/* spaces */
	errno = 0;
	strtol(spaces, &p, 0);
	if(p != spaces || errno != ERANGE)
	{
		fprintf(stderr, "%s: %s: Conversion error (spaces)\n", progname,
				"strtol");
		return 1;
	}
	/* -LONG_MAX - 1 */
	lu = (unsigned long)LONG_MAX + 1;
	snprintf(buf, sizeof(buf), "-%lu", lu);
	errno = 0;
	l = strtol(buf, &p, 10);
	if(errno != 0)
	{
		fprintf(stderr, "%s: %s: Conversion error (-LONG_MAX - 1)\n",
				progname, "strtol");
		return 1;
	}
	/* -LONG_MAX - 2 */
	lu = (unsigned long)LONG_MAX + 2;
	snprintf(buf, sizeof(buf), "-%lu", lu);
	errno = 0;
	strtol(buf, &p, 10);
	if(errno != ERANGE)
	{
		fprintf(stderr, "%s: %s: Conversion error (-LONG_MAX - 2)\n",
				progname, "strtol");
		return 1;
	}
	/* invalid input */
	l = strtol("invalid", &p, 0);
	if(l != 0 || errno != EINVAL)
	{
		fprintf(stderr, "%s: %s: Conversion error (invalid input)\n",
				progname, "strtol");
		return 1;
	}
	return 0;
}


/* strtoll */
static int _strtoll(char const * progname)
{
	char * p;
	char const spaces[] = "      ";
	long long ll;
	unsigned long long llu;
	char buf[32];

	/* spaces */
	errno = 0;
	strtoll(spaces, &p, 0);
	if(p != spaces || errno != ERANGE)
	{
		fprintf(stderr, "%s: %s: Conversion error (spaces)\n", progname,
				"strtol");
		return 1;
	}
	/* -LLONG_MAX - 1 */
	llu = (unsigned long long)LLONG_MAX + 1;
	snprintf(buf, sizeof(buf), "-%llu", llu);
	errno = 0;
	ll = strtoll(buf, &p, 10);
	if(errno != 0)
	{
		fprintf(stderr, "%s: %s: Conversion error (-LLONG_MAX - 1)\n",
				progname, "strtoll");
		return 1;
	}
	/* -LLONG_MAX - 2 */
	llu = (unsigned long)LLONG_MAX + 2;
	snprintf(buf, sizeof(buf), "-%llu", llu);
	errno = 0;
	strtoll(buf, &p, 10);
	if(errno != ERANGE)
	{
		fprintf(stderr, "%s: %s: Conversion error (-LLONG_MAX - 2)\n",
				progname, "strtoll");
		return 1;
	}
	/* invalid input */
	ll = strtoll("invalid", &p, 0);
	if(ll != 0 || errno != EINVAL)
	{
		fprintf(stderr, "%s: %s: Conversion error (invalid input)\n",
				progname, "strtoll");
		return 1;
	}
	return 0;
}


/* strtoul */
static int _strtoul(char const * progname)
{
	char * p;
	char const spaces[] = "      ";
	char buf[32];

	/* spaces */
	errno = 0;
	strtoul(spaces, &p, 0);
	if(p != spaces || errno != ERANGE)
	{
		fprintf(stderr, "%s: %s: Conversion error (spaces)\n", progname,
				"strtoul");
		return 1;
	}
	/* ULONG_MAX */
	snprintf(buf, sizeof(buf), "%lu", ULONG_MAX);
	errno = 0;
	strtoul(buf, &p, 10);
	if(errno != 0 || *p != '\0')
	{
		fprintf(stderr, "%s: %s: Conversion error (ULONG_MAX)\n",
				progname, "strtoul");
		return 1;
	}
	return 0;
}


/* strtoull */
static int _strtoull(char const * progname)
{
	char * p;
	char const spaces[] = "      ";
	char buf[32];

	/* spaces */
	errno = 0;
	strtoull(spaces, &p, 0);
	if(p != spaces || errno != ERANGE)
	{
		fprintf(stderr, "%s: %s: Conversion error (spaces)\n", progname,
				"strtoul");
		return 1;
	}
	/* ULLONG_MAX */
	snprintf(buf, sizeof(buf), "%llu", ULLONG_MAX);
	errno = 0;
	strtoull(buf, &p, 10);
	if(errno != 0 || *p != '\0')
	{
		fprintf(stderr, "%s: %s: Conversion error (ULLONG_MAX)\n",
				progname, "strtoul");
		return 1;
	}
	return 0;
}


/* public */
/* functions */
/* main */
int main(int argc, char * argv[])
{
	int ret = 0;
	(void) argc;

	ret += _arc4random(argv[0]);
	ret += _calloc(argv[0]);
	ret += _environ(argv[0]);
	ret += _mkstemp(argv[0]);
	ret += _mktemp(argv[0]);
	ret += _rand(argv[0]);
	ret += _realloc(argv[0]);
	ret += _strtold(argv[0], "0.0", 0.0);
	ret += _strtold(argv[0], " 0.1", 0.1);
	ret += _strtold(argv[0], "  1.0", 1.0);
	ret += _strtold(argv[0], "+1.1", 1.1);
	ret += _strtold(argv[0], "+1.01", 1.01);
	ret += _strtold(argv[0], "-1.1", -1.1);
	ret += _strtold(argv[0], "-1.01", -1.01);
	ret += _strtol(argv[0]);
	ret += _strtoul(argv[0]);
	ret += _strtoll(argv[0]);
	ret += _strtoull(argv[0]);
	return (ret == 0) ? 0 : 2;
}
