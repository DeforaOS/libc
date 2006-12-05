/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#ifndef LIBC_COMMON_H
# define LIBC_COMMON_H


/* settings */
# define NETBSD_USE_LINUX_EMULATION


/* settings code */
# if defined(__NetBSD__) && defined(NETBSD_USE_LINUX_EMULATION)
#  undef __NetBSD__
#  define __linux__
# endif

#endif /* !LIBC_COMMON_H */
