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



#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "regex.h"
#include "dlfcn.h"
#include "regex/pcre/pcre.h"
/* XXX */
#undef PACKAGE
#undef VERSION
#include "../config.h"

#ifndef PREFIX
# define PREFIX		"/usr/local"
#endif
#ifndef LIBDIR
# define LIBDIR		PREFIX "/lib"
#endif


/* private */
/* prototypes */
static int _pcre_init(void);


/* variables */
static struct
{
	int error;
	char const * message;
} _messages[] =
{
	{ REG_NOMATCH,	"No match"					},
	{ REG_BADPAT,	"Invalid regular expression"			},
	{ REG_ECOLLATE,	"Invalid collating element referenced"		},
	{ REG_ECTYPE,	"Invalid character class type referenced"	},
	{ REG_EESCAPE,	"Trailing '\\' in pattern"			},
	{ REG_ESUBREG,	"Number in \\digit invalid or in error"		},
	{ REG_EBRACK,	"\"[]\" imbalance"				},
	{ REG_EPAREN,	"\"\\(\\)\" or \"()\" imbalance"		},
	{ REG_EBRACE,	"\"\\{\\}\" imbalance"				},
	{ REG_BADBR,	"Content of \"\\{\\}\" invalid"			},
	{ REG_ERANGE,	"Invalid endpoint in range expression"		},
	{ REG_ESPACE,	"Out of memory"					},
	{ REG_BADRPT,	"'?', '*', or '+' not preceded by valid regular"
		" expression"						},
	{ REG_ENOSYS,	"Not implemented"				}
};

static void * _pcre_handle = NULL;

static void * (*_pcre_compile2)(const char *, int, int *, const char **,
                  int *, const unsigned char *);
static int (*_pcre_exec)(const void *, const void *, const char *,
                   int, int, int, int *, int);
static int (*_pcre_fullinfo)(const void *, const void *, int,
                  void *);


/* public */
/* functions */
/* regcomp */
static int _regcomp_error(int error);

int regcomp(regex_t * regex, const char * pattern, int flags)
{
	int pflags = 0;
	int perror = 0;
	const char * p;
	int poffset;
	int nsub;

	if(_pcre_init() != 0)
		return REG_ENOSYS;
	/* XXX implement more flags */
	if(flags & REG_ICASE)
		pflags |= PCRE_CASELESS;
	if(flags & REG_NEWLINE)
		pflags |= PCRE_MULTILINE;
	if((regex->re_pcre = _pcre_compile2(pattern, pflags, &perror, &p,
					&poffset, NULL)) == NULL)
		return _regcomp_error(perror);
	_pcre_fullinfo(regex->re_pcre, NULL, PCRE_INFO_CAPTURECOUNT, &nsub);
	regex->re_nsub = nsub;
	return 0;
}

static int _regcomp_error(int error)
{
	switch(error)
	{
		case 1:
		case 2:
		case 3:
			return REG_EESCAPE;
		case 4:
		case 5:
			return REG_BADBR;
		case 8:
			return REG_ERANGE;
		default:
			return REG_ENOSYS;
	}
}


/* regerror */
size_t regerror(int error, const regex_t * regex, char * buf, size_t buf_cnt)
{
	size_t i;
	char const * message = "Unknown error";
	int res;
	(void) regex;

	for(i = 0; i < sizeof(_messages) / sizeof(*_messages); i++)
		if(_messages[i].error == error)
		{
			message = _messages[i].message;
			break;
		}
	if((res = snprintf(buf, buf_cnt, "%s", message)) <= 0)
		return 0;
	return res + 1;
}


/* regexec */
static int _regexec_error(int error);

int regexec(const regex_t * regex, const char * string, size_t match_cnt,
		regmatch_t match[], int flags)
{
	int pflags = 0;
	int * pmatch;
	int res;
	size_t i;

	if(_pcre_init() != 0)
		return REG_ENOSYS;
	if(flags & REG_NOTBOL)
		pflags |= PCRE_NOTBOL;
	if(flags & REG_NOTEOL)
		pflags |= PCRE_NOTEOL;
	if(match_cnt > 0)
	{
		if((pmatch = malloc(sizeof(*pmatch) * match_cnt * 3)) == NULL)
			return REG_ESPACE;
	}
	else
		pmatch = NULL;
	if((res = _pcre_exec(regex->re_pcre, NULL, string, strlen(string), 0,
					pflags, pmatch, match_cnt * 3)) >= 0)
	{
		for(i = 0; i < match_cnt; i++)
		{
			match[i].rm_so = pmatch[i * 2];
			match[i].rm_eo = pmatch[i * 2 + 1];
		}
		free(pmatch);
		return 0;
	}
	free(pmatch);
	return _regexec_error(res);
}

static int _regexec_error(int error)
{
	switch(error)
	{
		case PCRE_ERROR_NOMATCH:
			return REG_NOMATCH;
		case PCRE_ERROR_MATCHLIMIT:
		case PCRE_ERROR_NOMEMORY:
			return REG_ESPACE;
		default:
			return REG_ENOSYS;
	}
}


/* regfree */
void regfree(regex_t * regex)
{
	free(regex->re_pcre);
}


/* private */
/* pcre_init */
static int _pcre_init(void)
{
	if(_pcre_handle != NULL)
		return 0;
	if((_pcre_handle = __dlopen(LIBDIR "/libpcre.so", RTLD_NOW)) == NULL
			&& (_pcre_handle = __dlopen(NULL, RTLD_NOW)) == NULL)
		return -1;
	if((_pcre_compile2 = __dlsym(_pcre_handle, "pcre_compile2")) == NULL
			|| (_pcre_exec = __dlsym(_pcre_handle, "pcre_exec"))
			== NULL
			|| (_pcre_fullinfo = __dlsym(_pcre_handle,
					"pcre_fullinfo")) == NULL)
	{
		__dlclose(_pcre_handle);
		_pcre_handle = NULL;
		return -1;
	}
	return 0;
}
