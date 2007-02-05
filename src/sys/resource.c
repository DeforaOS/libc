/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#include "../syscalls.h"
#include "sys/resource.h"


/* functions */
/* getpriority */
#ifndef SYS_getpriority
# warning Unsupported platform: getpriority() is missing
#endif

/* getrlimit */
#ifndef SYS_getrlimit
# warning Unsupported platform: getrlimit() is missing
#endif

/* setpriority */
#ifndef SYS_setpriority
# warning Unsupported platform: setpriority() is missing
#endif

/* setrlimit */
#ifndef SYS_setrlimit
# warning Unsupported platform: setrlimit() is missing
#endif
