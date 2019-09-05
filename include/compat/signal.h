/* $Id$ */
/* Copyright (c) 2007-2019 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_COMPAT_SIGNAL_H
# define LIBC_COMPAT_SIGNAL_H


# if defined(__APPLE__)
#  include "kernel/darwin/signal.h"
# elif defined(__DeforaOS__)
#  include "kernel/deforaos/signal.h"
# elif defined(__FreeBSD__)
#  include "kernel/freebsd/signal.h"
# elif defined(__linux__)
#  include "kernel/linux/signal.h"
# elif defined(__NetBSD__)
#  include "kernel/netbsd/signal.h"
# elif defined(__OpenBSD__)
#  include "kernel/openbsd/signal.h"
# elif defined(__Whitix__)
#  include "kernel/whitix/signal.h"
# else
#  warning Unsupported platform
# endif

#endif /* !LIBC_COMPAT_SIGNAL_H */
