/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#include "../syscalls.h"
#include "sys/utsname.h"


/* uname */
#ifndef __NetBSD__
syscall1(int, uname, struct utsname *, utsname);
#endif
