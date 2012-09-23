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
