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



#ifndef LIBC_REGEX_H
# define LIBC_REGEX_H


/* types */
typedef long regoff_t;
# ifndef size_t
#  define size_t size_t
typedef unsigned long size_t;
# endif

typedef struct
{
	size_t re_nsub;
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
