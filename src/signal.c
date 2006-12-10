/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#include "syscalls.h"
#include "signal.h"


/* kill */
syscall2(int, kill, pid_t, pid, int, sig);
