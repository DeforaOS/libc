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
#ifdef HAVE_CONFIG_H
# include "regex/config.h"
#endif
#include "regex/pcre.h"


/* private */
/* prototypes */
static int _regerror_pcre(int error);


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


/* public */
/* functions */
/* regcomp */
int regcomp(regex_t * regex, const char * pattern, int flags)
{
	int pflags = 0;
	int perror = 0;
	int nsub;

	/* XXX implement more flags */
	if(flags & REG_ICASE)
		pflags |= PCRE_CASELESS;
	if(flags & REG_NEWLINE)
		pflags |= PCRE_MULTILINE;
	if((regex->re_pcre = pcre_compile2(pattern, pflags, &perror, NULL, NULL,
					NULL)) == NULL)
		return _regerror_pcre(perror);
	pcre_fullinfo(regex->re_pcre, NULL, PCRE_INFO_CAPTURECOUNT, &nsub);
	regex->re_nsub = nsub;
	return 0;
}


/* regerror */
size_t regerror(int error, const regex_t * regex, char * buf, size_t buf_cnt)
{
	size_t i;
	char const * message = "Unknown error";
	int res;

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
int regexec(const regex_t * regex, const char * string, size_t match_cnt,
		regmatch_t match[], int flags)
{
	int pflags = 0;
	int * pmatch;
	int res;
	size_t i;

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
	if((res = pcre_exec(regex->re_pcre, NULL, string, strlen(string), 0,
					pflags, pmatch, match_cnt * 3)) == 0)
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
	return _regerror_pcre(res);
}


/* regfree */
void regfree(regex_t * regex)
{
	free(regex->re_pcre);
}


/* private */
/* regerror_pcre */
static int _regerror_pcre(int error)
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
