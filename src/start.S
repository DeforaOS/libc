/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



.text
.global _start


/* Linux */
#if defined(__linux__)
# include "kernel/linux/common.h"
# if defined(__i386__)
#  include "kernel/linux/i386/start.S"
# else /* !__i386__ */
#  warning Unsupported Linux architecture
# endif

/* NetBSD */
#elif defined(__NetBSD__)
# include "kernel/netbsd/common.h"
# if defined(__i386__)
#  include "kernel/netbsd/i386/start.S"
# else /* !__i386__ */
#  warning Unsupported NetBSD architecture
# endif

/* Unknown */
#else
# warning Unsupported kernel and architecture
#endif
