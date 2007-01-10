/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#include "../syscalls.h"
#include "sys/utsname.h"


/* uname */
#ifdef SYS_uname
syscall1(int, uname, struct utsname *, utsname);
#endif
