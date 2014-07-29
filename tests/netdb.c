/* $Id$ */
/* Copyright (c) 2013 Pierre Pronchery <khorben@defora.org> */
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



#include <stdio.h>
#include <netdb.h>


/* prototypes */
static int _netdb(char const * progname);

static int _gai_strerror(char const * progname, char const * message,
		int value);
static int _gethostent(void);
static int _getprotoent(void);
static int _getservbyname(char const * name, char const * protocol);
static int _getservbyport(int port, char const * protocol);
static int _getservent(void);
static int _hstrerror(char const * progname, char const * message, int value);


/* functions */
/* netdb */
static int _netdb(char const * progname)
{
	int ret = 0;

	/* gethostent */
	ret |= _gethostent();
	/* getprotoent */
	ret |= _getprotoent();
	/* getservent */
	ret |= _getservbyname("ssh", "tcp");
	ret |= _getservbyport(22, "tcp");
	ret |= _getservent();
	/* hstrerror */
	ret |= _hstrerror(progname, "HOST_NOT_FOUND", HOST_NOT_FOUND);
	ret |= _hstrerror(progname, "TRY_AGAIN", TRY_AGAIN);
	ret |= _hstrerror(progname, "NO_RECOVERY", NO_RECOVERY);
	ret |= _hstrerror(progname, "NO_DATA", NO_DATA);
	/* gai_strerror */
	ret |= _gai_strerror(progname, "EAI_AGAIN", EAI_AGAIN);
	ret |= _gai_strerror(progname, "EAI_BADFLAGS", EAI_BADFLAGS);
	ret |= _gai_strerror(progname, "EAI_FAIL", EAI_FAIL);
	ret |= _gai_strerror(progname, "EAI_FAMILY", EAI_FAMILY);
	ret |= _gai_strerror(progname, "EAI_MEMORY", EAI_MEMORY);
	ret |= _gai_strerror(progname, "EAI_NONAME", EAI_NONAME);
	ret |= _gai_strerror(progname, "EAI_OVERFLOW", EAI_OVERFLOW);
	ret |= _gai_strerror(progname, "EAI_SERVICE", EAI_SERVICE);
	ret |= _gai_strerror(progname, "EAI_SOCKTYPE", EAI_SOCKTYPE);
	ret |= _gai_strerror(progname, "EAI_SYSTEM", EAI_SYSTEM);
	return 0;
}


/* gai_strerror */
static int _gai_strerror(char const * progname, char const * message,
		int value)
{
	printf("%s: %s: %s\n", progname, message, gai_strerror(value));
	return 0;
}


/* gethostent */
static int _gethostent(void)
{
	struct hostent * he;
	unsigned int i;

	sethostent(1);
	for(i = 0; (he = gethostent()) != NULL; i++)
		printf("%s\t%d %d\n", he->h_name, he->h_addrtype, he->h_length);
	endhostent();
	printf("%u hosts listed\n", i);
	return 0;
}


/* getprotoent */
static int _getprotoent(void)
{
	struct protoent * pe;
	unsigned int i;

	setprotoent(1);
	for(i = 0; (pe = getprotoent()) != NULL; i++)
		printf("%s\t%d\n", pe->p_name, pe->p_proto);
	endprotoent();
	printf("%u protocols listed\n", i);
	return 0;
}


/* getservbyname */
static int _getservbyname(char const * name, char const * protocol)
{
	struct servent * se;

	printf("%s: %s/%s\n", "getservbyname", name, protocol);
	if((se = getservbyname(name, protocol)) == NULL)
		return 0;
	printf("%s\t%d/%s\n", se->s_name, se->s_port, se->s_proto);
	return 0;
}


/* getservbyport */
static int _getservbyport(int port, char const * protocol)
{
	struct servent * se;

	printf("%s: %d/%s\n", "getservbyport", port, protocol);
	if((se = getservbyport(port, protocol)) == NULL)
		return 0;
	printf("%s\t%d/%s\n", se->s_name, se->s_port, se->s_proto);
	return 0;
}


/* getservent */
static int _getservent(void)
{
	struct servent * se;
	unsigned int i;

	printf("%s:\n", "getservent");
	setservent(1);
	for(i = 0; (se = getservent()) != NULL; i++)
		printf("%s\t%d/%s\n", se->s_name, se->s_port, se->s_proto);
	endservent();
	printf("%u services listed\n", i);
	return 0;
}


/* hstrerror */
static int _hstrerror(char const * progname, char const * message, int value)
{
	printf("%s: %s: %s\n", progname, message, hstrerror(value));
	return 0;
}


/* main */
int main(int argc, char * argv[])
{
	int ret = 0;

	ret |= _netdb(argv[0]);
	return (ret == 0) ? 0 : 2;
}
