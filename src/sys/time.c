/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#include "../syscalls.h"
#include "sys/time.h"


/* functions */
syscall2(int, gettimeofday, struct timeval *, tv, void *, null);
