/* $Id$ */
/* Copyright (c) 2005-2013 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_PWD_H
# define LIBC_PWD_H


/* types */
# ifndef gid_t
#  define gid_t gid_t
typedef __gid_t gid_t;
# endif
# ifndef id_t
#  define id_t id_t
typedef __id_t id_t;
# endif
# ifndef uid_t
#  define uid_t uid_t
typedef __uid_t uid_t;
# endif

struct passwd
{
	char * pw_name;
	char * pw_passwd;
	uid_t pw_uid;
	gid_t pw_gid;
	char * pw_gecos;
	char * pw_dir;
	char * pw_shell;
};


/* functions */
struct passwd * getpwnam(char const * name);
int getpwnam_r(char const * name, struct passwd * pw, char * buffer,
		size_t bufsize, struct passwd ** result);
struct passwd * getpwuid(uid_t uid);

struct passwd * getpwent(void);
void endpwent(void);
void setpwent(void);

#endif /* !LIBC_PWD_H */
