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



#ifndef LIBC_KERNEL_WHITIX_SYS_UTSNAME_H
# define LIBC_KERNEL_WHITIX_SYS_UTSNAME_H


/* FIXME nothing checked */
/* struct utsname */
# define _UTSNAME_SIZE			65
# define _UTSNAME_SYSNAME_SIZE		_UTSNAME_SIZE
# define _UTSNAME_NODENAME_SIZE		_UTSNAME_SIZE
# define _UTSNAME_RELEASE_SIZE		_UTSNAME_SIZE
# define _UTSNAME_VERSION_SIZE		_UTSNAME_SIZE
# define _UTSNAME_MACHINE_SIZE		_UTSNAME_SIZE
# define _UTSNAME_PADDING_SIZE		_UTSNAME_SIZE

#endif /* !LIBC_KERNEL_WHITIX_SYS_UTSNAME_H */
