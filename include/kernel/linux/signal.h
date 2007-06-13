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



#ifndef LIBC_KERNEL_LINUX_SIGNAL_H
# define LIBC_KERNEL_LINUX_SIGNAL_H


/* constants */
# define SIGHUP		1
# define SIGINT		2
# define SIGQUIT	3
# define SIGILL		4
# define SIGTRAP	5
# define SIGABRT	6
# define SIGIOT		6
# define SIGBUS		7
# define SIGFPE		8
# define SIGKILL	9
# define SIGUSR1	10
# define SIGSEGV	11
# define SIGUSR2	12
# define SIGPIPE	13
# define SIGALRM	14
# define SIGTERM	15
# define SIGCHLD	17
# define SIGCONT	18
# define SIGSTOP	19

#endif /* !LIBC_KERNEL_LINUX_SIGNAL_H */
