/* $Id$ */
/* Copyright (c) 2012-2024 Pierre Pronchery <khorben@defora.org> */
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
#include "regex/pcre2/pcre2.h"
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
static int _pcre2_init(void);


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

static void * _pcre2_handle = NULL;

static pcre2_code * (*_pcre2_compile)(PCRE2_SPTR, PCRE2_SIZE,
		uint32_t, int *, PCRE2_SIZE *, pcre2_compile_context *);
static int (*_pcre2_pattern_info)(const pcre2_code *, uint32_t, void *);
static int (*_pcre2_match)(const pcre2_code *, PCRE2_SPTR,
		PCRE2_SIZE, PCRE2_SIZE, uint32_t,
		pcre2_match_data *, pcre2_match_context *);
static pcre2_match_data * (*_pcre2_match_data_create_from_pattern)(
		const pcre2_code *, pcre2_general_context *);
static void (*_pcre2_match_data_free)(pcre2_match_data *);
static PCRE2_SIZE * (*_pcre2_get_ovector_pointer)(pcre2_match_data *);


/* public */
/* functions */
/* regcomp */
static int _regcomp_error(int error);

int regcomp(regex_t * regex, const char * pattern, int flags)
{
	uint32_t pflags = 0;
	int perror = 0;
	PCRE2_SIZE poffset;
	uint32_t nsub;

	if(_pcre2_init() != 0)
		return REG_ENOSYS;
	/* XXX implement more flags */
	if(flags & REG_ICASE)
		pflags |= PCRE2_CASELESS;
	if(flags & REG_NEWLINE)
		pflags |= PCRE2_MULTILINE;
	if((regex->re_pcre = _pcre2_compile((PCRE2_SPTR)pattern,
					PCRE2_ZERO_TERMINATED, pflags, &perror,
					&poffset, NULL)) == NULL)
		return _regcomp_error(perror);
	if((perror = _pcre2_pattern_info(regex->re_pcre,
					PCRE2_INFO_CAPTURECOUNT, &nsub)) != 0)
	{
		regfree(regex);
		return _regcomp_error(perror);
	}
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
	uint32_t pflags = 0;
	pcre2_match_data * pmatch;
	int res;
	PCRE2_SIZE * ovector;
	size_t i;

	if(_pcre2_init() != 0)
		return REG_ENOSYS;
	if(flags & REG_NOTBOL)
		pflags |= PCRE2_NOTBOL;
	if(flags & REG_NOTEOL)
		pflags |= PCRE2_NOTEOL;
	if(match_cnt > 0)
	{
		if((pmatch = _pcre2_match_data_create_from_pattern(
						regex->re_pcre, NULL)) == NULL)
			return REG_ESPACE;
	}
	else
		pmatch = NULL;
	if((res = _pcre2_match((pcre2_code *)regex->re_pcre, (PCRE2_SPTR)string,
					(PCRE2_SIZE)strlen(string), 0,
					pflags, pmatch, NULL)) < 0)
	{
		if(pmatch != NULL)
			_pcre2_match_data_free(pmatch);
		return _regexec_error(res);
	}
	ovector = _pcre2_get_ovector_pointer(pmatch);
	for(i = 0; i < (size_t)res && i < match_cnt; i++)
	{
		match[i].rm_so = ovector[2 * i];
		match[i].rm_eo = ovector[(2 * i) + 1];
	}
	if(pmatch != NULL)
		_pcre2_match_data_free(pmatch);
	return 0;
}

static int _regexec_error(int error)
{
	switch(error)
	{
		case PCRE2_ERROR_NOMATCH:
			return REG_NOMATCH;
		case PCRE2_ERROR_MATCHLIMIT:
		case PCRE2_ERROR_NOMEMORY:
			return REG_ESPACE;
		default:
			return REG_ENOSYS;
	}
}


/* regfree */
void regfree(regex_t * regex)
{
	free(regex->re_pcre);
	regex->re_pcre = NULL;
}


/* private */
/* pcre2_init */
static void * _init_dlopen(char const * path, int mode);

static int _pcre2_init(void)
{
	if(_pcre2_handle != NULL)
		return 0;
	if((_pcre2_handle = _init_dlopen(NULL, RTLD_NOW)) == NULL
			&& (_pcre2_handle = _init_dlopen(LIBDIR "/libpcre2.so",
					RTLD_NOW)) == NULL)
		return -1;
	return 0;
}

static void * _init_dlopen(char const * path, int mode)
{
	void * ret;

	if((ret = __dlopen(path, mode)) == NULL)
		return NULL;
	if((_pcre2_compile = __dlsym(ret, "pcre2_compile_8")) == NULL
			|| (_pcre2_pattern_info = __dlsym(ret,
					"pcre2_pattern_info_8")) == NULL
			|| (_pcre2_match = __dlsym(ret,
					"pcre2_match_8")) == NULL
			|| (_pcre2_match_data_create_from_pattern = __dlsym(ret,
					"pcre2_match_data_create_from_pattern_8"))
			== NULL
			|| (_pcre2_match_data_free = __dlsym(ret,
					"pcre2_match_data_free_8")) == NULL
			|| (_pcre2_get_ovector_pointer = __dlsym(ret,
					"pcre2_get_ovector_pointer_8")) == NULL)
	{
		__dlclose(ret);
		return NULL;
	}
	return ret;
}
