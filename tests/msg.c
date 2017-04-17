/* $Id$ */
/* Copyright (c) 2017 Pierre Pronchery <khorben@defora.org> */
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



#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


/* msgctl */
static int _msgctl(char const * progname)
{
	int qid;
	struct msqid_ds ds;
	int d;

	printf("%s: Testing %s()\n", progname, "msgctl");
	if((qid = msgget(IPC_PRIVATE, IPC_CREAT)) == -1)
	{
		printf("%s: msgget(IPC_PRIVATE) => %d (%s)\n", progname, qid,
				strerror(errno));
		return 2;
	}
	if((d = msgctl(qid, IPC_STAT, &ds)) != 0)
		printf("%s: msgctl(IPC_STAT) => %d (%s)\n", progname, d,
				strerror(errno));
	if((d = msgctl(qid, IPC_RMID, NULL)) != 0)
	{
		printf("%s: msgctl(IPC_RMID) => %d (%s)\n", progname, d,
				strerror(errno));
		return 2;
	}
	return 0;
}


/* main */
int main(int argc, char * argv[])
{
	int ret = 0;

	ret |= _msgctl(argv[0]);
	return (ret == 0) ? 0 : 2;
}
