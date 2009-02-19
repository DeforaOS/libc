/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBSOCKET_ARPA_INET_H
# define LIBSOCKET_ARPA_INET_H

# include <netinet/in.h>


/* functions */
uint32_t htonl(uint32_t host32);
uint16_t htons(uint16_t host16);
uint32_t ntohl(uint32_t net32);
uint16_t ntohs(uint16_t net16);

#endif /* !LIBSOCKET_ARPA_INET_H */
