/* $Id$ */
/* Copyright (c) 2007-2020 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_COMPAT_TERMIOS_H
# define LIBC_COMPAT_TERMIOS_H


# if defined(__DeforaOS__)
#  include "kernel/deforaos/termios.h"
# elif defined(__APPLE__)
#  include "kernel/darwin/termios.h"
# elif defined(__linux__)
#  include "kernel/linux/termios.h"
# elif defined(__FreeBSD__)
#  include "kernel/freebsd/termios.h"
# elif defined(__NetBSD__)
#  include "kernel/netbsd/termios.h"
# elif defined(__OpenBSD__)
#  include "kernel/openbsd/termios.h"
# elif defined(__Whitix__)
#  include "kernel/whitix/termios.h"
# else
#  warning Unsupported platform
# endif

#endif /* !LIBC_COMPAT_TERMIOS_H */
