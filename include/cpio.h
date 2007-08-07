/* $Id$ */
/* Copyright (c) 2007 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_CPIO_H
# define LIBC_CPIO_H


/* constants */
# define C_IRUSR	0000400
# define C_IWUSR	0000200
# define C_IXUSR	0000100
# define C_IRGRP	0000040
# define C_IWGRP	0000020
# define C_IXGRP	0000010
# define C_IROTH	0000004
# define C_IWOTH	0000002
# define C_IXOTH	0000001
# define C_ISUID	0004000
# define C_ISGID	0002000
# define C_ISVTX	0001000
# define C_ISDIR	0040000
# define C_ISFIFO	0010000
# define C_ISREG	0100000
# define C_ISBLK	0060000
# define C_ISCHR	0020000
# define C_ISCTG	0110000
# define C_ISLNK	0120000
# define C_ISSOCK	0140000

# define MAGIC		"070707"

#endif /* !LIBC_CPIO_H */
