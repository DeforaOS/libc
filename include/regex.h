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



#ifndef LIBC_REGEX_H
# define LIBC_REGEX_H

# include "compat.h"


/* types */
typedef long regoff_t;
# ifndef size_t
#  define size_t size_t
typedef __size_t size_t;
# endif

typedef struct
{
	size_t re_nsub;
	void * re_pcre;
} regex_t;

typedef struct
{
	regoff_t rm_so;
	regoff_t rm_eo;
} regmatch_t;


/* constants */
/* regcomp */
# define REG_EXTENDED	0x1
# define REG_ICASE	0x2
# define REG_NOSUB	0x4
# define REG_NEWLINE	0x8

/* regerror */
# define REG_NOMATCH	1
# define REG_BADPAT	2
# define REG_ECOLLATE	3
# define REG_ECTYPE	4
# define REG_EESCAPE	5
# define REG_ESUBREG	6
# define REG_EBRACK	7
# define REG_EPAREN	8
# define REG_EBRACE	9
# define REG_BADBR	10
# define REG_ERANGE	11
# define REG_ESPACE	12
# define REG_BADRPT	13
# define REG_ENOSYS	14

/* regexec */
# define REG_NOTBOL	0x1
# define REG_NOTEOL	0x2


/* functions */
int regcomp(regex_t * regex, const char * pattern, int flags);
size_t regerror(int error, const regex_t * regex, char * buf, size_t buf_cnt);
int regexec(const regex_t * regex, const char * string, size_t match_cnt,
		regmatch_t match[], int flags);
void regfree(regex_t * regex);

#endif /* !LIBC_REGEX_H */
