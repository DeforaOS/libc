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



#include "stdio.h"
#include "regex.h"


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


/* functions */
/* regcomp */
int regcomp(regex_t * regex, const char * pattern, int flags)
{
	/* FIXME really implement */
	regex->re_flags = flags;
	return REG_ENOSYS;
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
	/* FIXME really implement */
	return REG_ENOSYS;
}


/* regfree */
void regfree(regex_t * regex)
{
}
