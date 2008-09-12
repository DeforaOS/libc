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



#ifndef LIBC_ICONV_H
# define LIBC_ICONV_H


/* types */
typedef struct _iconv_t * iconv_t;


/* functions */
iconv_t iconv_open(const char * tocode, const char * fromcode);
size_t iconv(iconv_t cd, char ** inbuf, size_t * inbytesleft,
		char ** outbuf, size_t * outbytesleft);
int iconv_close(iconv_t cd);

#endif /* !LIBC_ICONV_H */
