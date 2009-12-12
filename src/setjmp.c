/* $Id$ */
/* Copyright (c) 2008 Pierre Pronchery <khorben@defora.org> */
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



#include "signal.h"
#include "setjmp.h"


/* functions */
/* setjmp */
/* XXX from dietlibc */
int _sigjmp_save(sigjmp_buf env, int savemask);

int _sigjmp_save(sigjmp_buf env, int savemask)
{
	env[0].__mask_was_saved = 0;
	if(savemask)
		env[0].__mask_was_saved = (sigprocmask(SIG_BLOCK, (sigset_t*)0,
					&env[0].__saved_mask) == 0);
	return 0;
}
