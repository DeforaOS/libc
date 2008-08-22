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



#ifndef SOCKET_KERNEL_LINUX_COMMON_H
# define SOCKET_KERNEL_LINUX_COMMON_H


# define SYS_socket		1
# define SYS_bind		2
# define SYS_listen		4
# define SYS_accept		5
# define SYS_recv		9
# define SYS_send		10
# define SYS_sendto		11
# define SYS_recvfrom		12
# define SYS_socketcall		102

#endif /* !KERNEL_SOCKET_LINUX_COMMON_H */
