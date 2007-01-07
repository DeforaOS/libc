/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#include "../syscalls.h"
#include "sys/utsname.h"


/* uname */
#if !defined(__NetBSD__) || defined(NETBSD_USE_LINUX_EMULATION)
syscall1(int, uname, struct utsname *, utsname);
#endif
