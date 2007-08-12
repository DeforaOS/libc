/* $Id$ */
/* Copyright (c) 2007 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* libc is not free software; you can redistribute it and/or modify it under
 * the terms of the Creative Commons Attribution-NonCommercial-ShareAlike 3.0
 * Unported as published by the Creative Commons organization.
 *
 * libc is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the Creative Commons Attribution-NonCommercial-
 * ShareAlike 3.0 Unported license for more details.
 *
 * You should have received a copy of the Creative Commons Attribution-
 * NonCommercial-ShareAlike 3.0 along with libc; if not, browse to
 * http://creativecommons.org/licenses/by-nc-sa/3.0/ */



#include "unistd.h"
#include "syscalls.h"
#include "signal.h"


/* kill */
#ifndef SYS_kill
# warning Unsupported platform: kill() is missing
#endif


/* raise */
int raise(int sig)
{
	return kill(getpid(), sig);
}


/* sigaction */
#ifndef SYS_sigaction
# warning Unsupported platform: sigaction() is missing
#endif


/* signal */
void (*signal(int sig, void (*func)(int)))
{
	struct sigaction sa;
	struct sigaction osa;

	sa.sa_handler = func;
	sigemptyset(&sa.sa_mask);
	if(sigaction(sig, &sa, &osa) != 0)
		return SIG_ERR;
	return osa.sa_handler;
}
