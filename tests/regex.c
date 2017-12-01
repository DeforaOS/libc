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



#include "../src/regex/pcre/pcre.h"
#include <regex.h>
#include <stdio.h>


/* regex */
static void _regex_regerror(char const * progname);
static int _regex_regexec(char const * progname, char const * pattern,
		char const * string, int flags);

static int _regex(char const * progname)
{
	int ret;

	ret = _regex_regexec(progname, "^test$", "test", 0);
	ret |= _regex_regexec(progname, "^test$", "TEST", REG_ICASE);
	_regex_regerror(progname);
	return ret;
}

static void _regex_regerror(char const * progname)
{
	const int errors[] =
	{
		REG_NOMATCH, REG_BADPAT, REG_ECOLLATE, REG_ECTYPE, REG_EESCAPE,
		REG_ESUBREG, REG_EBRACK, REG_EPAREN, REG_EBRACE, REG_BADBR,
		REG_ERANGE, REG_ESPACE, REG_BADRPT
	};
	char buf[80];
	size_t size;
	size_t i;

	for(i = 0; i < sizeof(errors) / sizeof(*errors); i++)
	{
		size = regerror(errors[i], NULL, buf, sizeof(buf));
		printf("%s: Testing %s: % 2u \"%s\" (%zu)\n", progname,
				"regerror()", errors[i], buf, size);
	}
}

static int _regex_regexec(char const * progname, char const * pattern,
		char const * string, int flags)
{
	int ret;
	regex_t reg;
	char buf[80];
	int r;
	regmatch_t match[1];

	printf("%s: Testing regexec(): \"%s\" \"%s\" (%d)\n", progname,
			pattern, string, flags);
	if((r = regcomp(&reg, pattern, flags)) != 0)
	{
		regerror(r, &reg, buf, sizeof(buf));
		fprintf(stderr, "%s: %s: %s\n", progname, pattern, buf);
		return 1;
	}
	if((ret = regexec(&reg, string, sizeof(match) / sizeof(*match), match,
					0)) != 0)
	{
		regerror(ret, &reg, buf, sizeof(buf));
		fprintf(stderr, "%s: %s: %s\n", progname, pattern, buf);
		ret = 1;
	}
	regfree(&reg);
	return ret;
}


/* XXX stub */
void stub(void)
{
	pcre_compile2(NULL, 0, NULL, NULL, NULL, NULL);
	pcre_exec(NULL, NULL, NULL, 0, 0, 0, NULL, 0);
	pcre_fullinfo(NULL, NULL, 0, NULL);
}


/* main */
int main(int argc, char * argv[])
{
	(void) argc;

	return (_regex(argv[0]) == 0) ? 0 : 2;
}
