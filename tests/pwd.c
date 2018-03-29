/* $Id$ */
/* Copyright (c) 2013-2017 Pierre Pronchery <khorben@defora.org> */
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



#include <stdio.h>
#include <pwd.h>


/* getpwent */
static int _getpwent(char const * progname)
{
	struct passwd * pw;

	setpwent();
	printf("%s: Testing getpwent()\n", progname);
	while((pw = getpwent()) != NULL)
		printf("%s: %s (%u:%u) %s\n", progname, pw->pw_name, pw->pw_uid,
				pw->pw_gid, pw->pw_shell);
	endpwent();
	return 0;
}


/* getpwnam */
static int _getpwnam(char const * progname)
{
	struct passwd * pw;

	printf("%s: Testing getpwnam()\n", progname);
	if((pw = getpwnam("root")) == NULL)
		return -1;
	printf("%s: %s:%s:%u:%u:%s:%s:%s\n", progname, pw->pw_name, "*",
			pw->pw_uid, pw->pw_gid, pw->pw_gecos, pw->pw_dir,
			pw->pw_shell);
	if(pw->pw_uid != 0)
		return -1;
	return 0;
}


/* main */
int main(int argc, char * argv[])
{
	int res = 0;
	(void) argc;

	res += _getpwnam(argv[0]);
	res += _getpwent(argv[0]);
	return (res == 0) ? 0 : 2;
}
