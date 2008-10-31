/* $Id$ */
/* Copyright (c) 2008 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. */



#ifndef LIBC_SYSLOG_H
# define LIBC_SYSLOG_H


/* constants */
# define	LOG_DAEMON		0
# define	LOG_EMERG		0
# define	LOG_ALERT		0
# define	LOG_CRIT		0
# define	LOG_ERR			0
# define	LOG_WARNING		0
# define	LOG_NOTICE		0
# define	LOG_INFO		0
# define	LOG_DEBUG		0
# define	LOG_PID			0
# define	LOG_CONS		0


/* functions */
void closelog(void);
void openlog(const char *ident, int logopt, int facility);
int setlogmask(int maskpri);
void syslog(int priority, const char *message, ... /* arguments */);

#endif /* LIBC_SYSLOG_H */
