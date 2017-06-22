/* $Id$ */
/* Copyright (c) 2005-2017 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_SIGNAL_H
# define LIBC_SIGNAL_H

# include "compat.h"


/* types */
# ifndef id_t
#  define id_t id_t
typedef __id_t id_t;
# endif
# ifndef pid_t
#  define pid_t pid_t
typedef __pid_t pid_t;
# endif
# ifndef sig_atomic_t
#  define sig_atomic_t sig_atomic_t
typedef int sig_atomic_t;
# endif
# ifndef uid_t
#  define uid_t uid_t
typedef __uid_t uid_t;
# endif

# include "compat/signal.h"


/* functions */
int kill(pid_t pid, int sig);
int raise(int sig);
int sigaction(int sig, const struct sigaction * act, struct sigaction * oact);
int sigaddset(sigset_t * set, int sig);
int sigdelset(sigset_t * set, int sig);
#ifndef sigemptyset
int sigemptyset(sigset_t * set);
#endif
#ifndef sigfillset
int sigfillset(sigset_t * set);
#endif
int sigismember(const sigset_t * set, int sig);
int sigprocmask(int how, const sigset_t * set, sigset_t * oset);
void (*signal(int sig, void (*func)(int)));

#endif /* !LIBC_SIGNAL_H */
