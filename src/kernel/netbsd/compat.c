/* $Id$ */



#if defined(__NetBSD__)
# include "sys/sysctl.h"
# include "../../syscalls.h"


/* sysctl */
syscall6(int, sysctl, int *, name, unsigned int, namecnt, void *, from,
		size_t *, fromsize, void *, to, size_t, tosize);

#endif /* __NetBSD__ */
