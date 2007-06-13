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



#include "../syscalls.h"
#include "sys/resource.h"


/* functions */
/* getpriority */
#ifndef SYS_getpriority
# warning Unsupported platform: getpriority() is missing
#endif


/* getrlimit */
#ifndef SYS_getrlimit
# warning Unsupported platform: getrlimit() is missing
#endif


/* getrusage */
#ifndef SYS_getrusage
# warning Unsupported platform: getrusage() is missing
#endif


/* setpriority */
#ifndef SYS_setpriority
# warning Unsupported platform: setpriority() is missing
#endif


/* setrlimit */
#ifndef SYS_setrlimit
# warning Unsupported platform: setrlimit() is missing
#endif
