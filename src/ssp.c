/* $Id$ */
/* Copyright (c) 2015 Pierre Pronchery <khorben@defora.org> */
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



#include "sys/sysctl.h"
#include "unistd.h"
#include "stdlib.h"
#include "syscalls.h"
#include "ssp.h"


#if defined(__SSP__)
/* variables */
long __stack_chk_guard[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };


/* functions */
/* stack_chk_fail */
void __stack_chk_fail(void)
{
	const char buf[] = "stack overflow detected: terminated\n";

	write(2, buf, sizeof(buf) - 1);
	abort();
	_exit(127);
}


#ifdef __i386__
/* stack_chk_fail_local */
void __stack_chk_fail_local(void)
{
	__stack_chk_fail();
}
#endif


/* stack_chk_setup */
void __stack_chk_setup(void)
{
#if defined(SYS_sysctl) && defined(CTL_KERN) && defined(KERN_ARND)
	const int mib[2] = { CTL_KERN, KERN_ARND };
	size_t len = sizeof(__stack_chk_guard);

	if(__stack_chk_guard[0] != 0)
		return;
	if(sysctl(mib, sizeof(mib) / sizeof(*mib), __stack_chk_guard, &len,
				NULL, 0) == -1
			|| len != sizeof(__stack_chk_guard))
#else
	if(__stack_chk_guard[0] == 0)
#endif
	{
		/* use the "terminator canary" */
		__stack_chk_guard[0] = 0;
		__stack_chk_guard[1] = 0;
		__stack_chk_guard[2] = '\n';
		__stack_chk_guard[3] = 255;
	}
}
#endif
