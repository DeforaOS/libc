/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_PWD_H
# define LIBC_PWD_H


/* types */
# ifndef id_t
#  define id_t id_t
typedef unsigned int id_t;
# endif
# ifndef gid_t
#  define gid_t gid_t
typedef id_t gid_t;
# endif
# ifndef uid_t
#  define uid_t uid_t
typedef id_t uid_t;
# endif

struct passwd
{
	char * pw_name;
	char * pw_passwd;
	uid_t pw_uid;
	gid_t pw_gid;
	char * pw_dir;
	char * pw_shell;
};


/* functions */
struct passwd * getpwnam(char const * name);
struct passwd * getpwuid(uid_t uid);

struct passwd * getpwent(void);
void endpwent(void);
void setpwent(void);

#endif /* !LIBC_PWD_H */
