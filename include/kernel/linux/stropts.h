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



#ifndef LIBC_KERNEL_LINUX_STROPTS_H
# define LIBC_KERNEL_LINUX_STROPTS_H


/* constants */
# define __SID		('S' << 8)
# define I_NREAD	(__SID | 1)
# define I_PUSH		(__SID | 2)
# define I_POP		(__SID | 3)
# define I_LOOK		(__SID | 4)
# define I_FLUSH	(__SID | 5)
# define I_SRDOPT	(__SID | 6)
# define I_GRDOPT	(__SID | 7)
# define I_STR		(__SID | 8)
# define I_SETSIG	(__SID | 9)
# define I_GETSIG	(__SID | 10)
# define I_FIND		(__SID | 11)
# define I_LINK		(__SID | 12)
# define I_UNLINK	(__SID | 13)
# define I_RECVFD	(__SID | 14)
# define I_PEEK		(__SID | 15)
# define I_FDINSERT	(__SID | 16)
# define I_SENDFD	(__SID | 17)
# undef __SID

#endif /* !LIBC_KERNEL_LINUX_STROPTS_H */
