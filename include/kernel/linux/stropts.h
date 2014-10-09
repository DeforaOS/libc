/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
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

#endif /* !LIBC_KERNEL_LINUX_STROPTS_H */
