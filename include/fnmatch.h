/* $Id$ */
/* Copyright (c) 2008 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_FNMATCH_H
# define LIBC_FNMATCH_H


/* constants */
# define FNM_NOMATCH	1
# define FNM_NOSYS	2

# define FNM_PATHNAME	0x1
# define FNM_PERIOD	0x2
# define FNM_NOESCAPE	0x4


/* functions */
int fnmatch(char const * pattern, char const * string, int flags);

#endif /* !LIBC_FNMATCH_H */
