/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#include "../syscalls.h"
#include "sys/select.h"


/* select */
#ifdef SYS_select
syscall5(int, select, int, fdcnt, fd_set *, rfds, fd_set *, wfds,
		fd_set *, efds, struct timeval *, timeout);
#endif /* !SYS_select */
