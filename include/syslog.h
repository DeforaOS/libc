/* $Id$ */
/* Copyright (c) 2008-2025 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_SYSLOG_H
# define LIBC_SYSLOG_H


/* constants */
/* options */
# define	LOG_PID			0x01
# define	LOG_CONS		0x02
# define	LOG_NDELAY		0x04
# define	LOG_ODELAY		0x08
# define	LOG_NOWAIT		0x10

/* facility */
# define	LOG_KERN		0x0000
# define	LOG_USER		0x0001
# define	LOG_MAIL		0x0002
# define	LOG_NEWS		0x0003
# define	LOG_UUCP		0x0004
# define	LOG_DAEMON		0x0005
# define	LOG_AUTH		0x0006
# define	LOG_CRON		0x0007
# define	LOG_LPR			0x0008
# define	LOG_LOCAL0		0x0010
# define	LOG_LOCAL1		0x0011
# define	LOG_LOCAL2		0x0012
# define	LOG_LOCAL3		0x0013
# define	LOG_LOCAL4		0x0014
# define	LOG_LOCAL5		0x0015
# define	LOG_LOCAL6		0x0016
# define	LOG_LOCAL7		0x0017

/* severity */
# define	LOG_EMERG		0x0000
# define	LOG_ALERT		0x0100
# define	LOG_CRIT		0x0200
# define	LOG_ERR			0x0300
# define	LOG_WARNING		0x0400
# define	LOG_NOTICE		0x0500
# define	LOG_INFO		0x0600
# define	LOG_DEBUG		0x0700


/* functions */
void closelog(void);
void openlog(const char * ident, int logopt, int facility);
int setlogmask(int maskpri);
void syslog(int priority, const char * message, ...);

#endif /* LIBC_SYSLOG_H */
