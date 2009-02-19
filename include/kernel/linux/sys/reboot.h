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



#ifndef LIBC_KERNEL_LINUX_SYS_REBOOT_H
# define LIBC_KERNEL_LINUX_SYS_REBOOT_H


/* constants */
/* reboot flag */
# define RF_HALT	0xcdef0123
# define RF_POWEROFF	0x4321fedc
# define RF_REBOOT	0x01234567

#endif /* !LIBC_KERNEL_LINUX_SYS_REBOOT_H */
