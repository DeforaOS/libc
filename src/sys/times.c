/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#include "../syscalls.h"
#include "sys/times.h"


/* times */
#ifndef __NetBSD__
syscall1(clock_t, times, struct tms *, buf);
#endif
