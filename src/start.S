/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



.section .text


/* _start */
.global _start


/* Linux */
#if defined(__linux__)
# if defined(__i386__)
#  include "kernel/linux/i386/start.S"
# elif defined(__sparc__)
#  include "kernel/linux/sparc/start.S"
# else /* !__i386__ && !__sparc__ */
#  warning Unsupported Linux architecture
# endif

/* NetBSD */
#elif defined(__NetBSD__)
# if defined(__i386__)
#  include "kernel/netbsd/i386/start.S"
# elif defined(__sparc__)
#  include "kernel/netbsd/sparc/start.S"
# else /* !__i386__ && !__sparc__ */
#  warning Unsupported NetBSD architecture
# endif
# include "kernel/netbsd/start.S"

/* Solaris */
#elif defined(__sun__)
# if defined(__sparc__)
#  include "kernel/solaris/sparc/start.S"
# else
#  warning Unsupported Solaris architecture
# endif

/* Unknown */
#else
# warning Unsupported kernel and architecture
#endif
