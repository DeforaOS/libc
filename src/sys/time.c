/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#include "../syscalls.h"
#include "sys/time.h"


/* functions */
/* gettimeofday */
#ifndef SYS_gettimeofday
# warning Unsupported platform: gettimeofday() is missing
#endif


/* utimes */
#ifndef SYS_utimes
# warning Unsupported platform: utimes() is missing
#endif
