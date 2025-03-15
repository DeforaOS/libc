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



#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "syslog.h"


/* private */
/* constants */
#define LOG_MASK_FACILITY	0x00ff
#define LOG_MASK_SEVERITY	0x0f00

const char * _log_severities[] =
{
	"EMERG",
	"ALERT",
	"CRITICAL",
	"ERROR",
	"WARNING",
	"NOTICE",
	"INFO",
	"DEBUG"
};


/* macros */
#define LOG_PRIORITY_GET_FACILITY(priority) (priority & LOG_MASK_FACILITY)
#define LOG_PRIORITY_GET_SEVERITY(priority) (priority & LOG_MASK_SEVERITY)


/* variables */
static struct
{
	char const * ident;
	unsigned int options;
	int fd;
	char const * filename;
} _log_facilities[LOG_LOCAL7 + 1] =
{
	{ NULL, 0, -1, "/var/log/kern.log"	},
	{ NULL, 0, -1, "/var/log/user.log"	},
	{ NULL, 0, -1, "/var/log/mail.log"	},
	{ NULL, 0, -1, "/var/log/news.log"	},
	{ NULL, 0, -1, "/var/log/uucp.log"	},
	{ NULL, 0, -1, "/var/log/daemon.log"	},
	{ NULL, 0, -1, "/var/log/auth.log"	},
	{ NULL, 0, -1, "/var/log/cron.log"	},
	{ NULL, 0, -1, "/var/log/lpr.log"	},
	{ NULL, 0, -1, NULL			},
	{ NULL, 0, -1, NULL			},
	{ NULL, 0, -1, NULL			},
	{ NULL, 0, -1, NULL			},
	{ NULL, 0, -1, NULL			},
	{ NULL, 0, -1, NULL			},
	{ NULL, 0, -1, NULL			},
	{ NULL, 0, -1, "/var/log/local0.log"	},
	{ NULL, 0, -1, "/var/log/local1.log"	},
	{ NULL, 0, -1, "/var/log/local2.log"	},
	{ NULL, 0, -1, "/var/log/local3.log"	},
	{ NULL, 0, -1, "/var/log/local4.log"	},
	{ NULL, 0, -1, "/var/log/local5.log"	},
	{ NULL, 0, -1, "/var/log/local6.log"	},
	{ NULL, 0, -1, "/var/log/local7.log"	}
};

static int _log_facility_default = LOG_USER;


/* prototypes */
static void _log_open(int facility);


/* public */
/* functions */
/* closelog */
void closelog(void)
{
	size_t i;

	for(i = 0; i < sizeof(_log_facilities) / sizeof(*_log_facilities); i++)
	{
		_log_facilities[i].ident = NULL;
		_log_facilities[i].options = 0;
		if(_log_facilities[i].fd >= 0)
		{
			close(_log_facilities[i].fd);
			_log_facilities[i].fd = 0;
		}
	}
}


/* openlog */
void openlog(const char * ident, int logopt, int facility)
{
	if(facility < 0 || facility >= (int)(sizeof(_log_facilities)
				/ sizeof(*_log_facilities)))
		return;
	_log_facilities[facility].ident = ident;
	_log_facilities[facility].options = logopt;
	if(_log_facilities[facility].fd >= 0)
		return;
	if(logopt & LOG_ODELAY)
		return;
	_log_open(facility);
}


/* setlogmask */
int setlogmask(int maskpri)
{
	static int oldmask = 0; /* FIXME check */
	int ret = oldmask;

	oldmask = maskpri;
	return ret;
}


/* syslog */
void syslog(int priority, const char * message, ...)
{
	const char sep[2] = ": ";
	int facility;
	int severity;
	int fd;
	char buf[1024];
	size_t size;
	time_t t;
	struct tm timeval;
	va_list ap;

	/* obtain the facility and severity */
	facility = LOG_PRIORITY_GET_FACILITY(priority);
	severity = LOG_PRIORITY_GET_SEVERITY(priority);
	if(facility < 0 || facility >= (int)(sizeof(_log_facilities)
				/ sizeof(*_log_facilities))
			|| _log_facilities[facility].filename == NULL)
		facility = _log_facility_default;
	severity >>= 8;
	if(severity < 0 || severity >= (int)(sizeof(_log_severities)
				/ sizeof(*_log_severities)))
		severity = 0; /* XXX LOG_EMERG */

	if((fd = _log_facilities[facility].fd) < 0)
		_log_open(facility);
	if((fd = _log_facilities[facility].fd) < 0)
		return;

	/* date & time (if not through syslogd) */
	if((t = time(NULL)) != (time_t)-1)
	{
		localtime_r(&t, &timeval);
		if((size = strftime(buf, sizeof(buf), "%d/%m/%Y %H:%M:%S ",
						&timeval)) > 0)
			write(fd, buf, size);
	}

	/* severity */
	size = strlen(_log_severities[severity]);
	write(fd, _log_severities[severity], size);
	if(_log_facilities[facility].ident != NULL)
	{
		size = strlen(_log_facilities[facility].ident);
		write(fd, _log_facilities[facility].ident, size);
	}

	/* PID (optional) */
	if(_log_facilities[facility].options & LOG_PID)
	{
		size = snprintf(buf, sizeof(buf), "[%u]", getpid());
		write(fd, buf, size);
	}

	/* separator */
	write(fd, sep, sizeof(sep));

	/* message */
	va_start(ap, message);
	size = vsnprintf(buf, sizeof(buf), message, ap);
	va_end(ap);
	write(fd, buf, size);

	/* new line */
	write(fd, "\n", 1);
}


/* private */
/* functions */
/* log_open */
static int _log_open_filename(int facility, char const * filename);

static void _log_open(int facility)
{
	char const * filename;

	if(_log_facilities[facility].fd < 0)
	{
		if((filename = _log_facilities[facility].filename) != NULL)
		{
			/* fallback to the console if requested */
			if(_log_open_filename(facility, filename) < 0
					&& (_log_facilities[facility].options
						& LOG_CONS) != 0)
				_log_open_filename(facility, "/dev/console");
			if(_log_facilities[facility].fd >= 0)
				return;
		}
		/* XXX fallback to stderr */
		_log_facilities[facility].fd = STDERR_FILENO;
	}
}

static int _log_open_filename(int facility, char const * filename)
{
	const int flags = O_WRONLY | O_APPEND | FD_CLOEXEC;

	_log_facilities[facility].fd = open(filename, flags);
	return _log_facilities[facility].fd;
}
