PACKAGE	= libc
VERSION	= 0.0.1
SUBDIRS	= src include
RM	= rm -f
LN	= ln -sf
TAR	= tar -czvf


all: subdirs

subdirs:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE)) || exit; done

clean:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) clean) || exit; done

distclean:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) distclean) || exit; done

dist:
	$(RM) -r $(PACKAGE)-$(VERSION)
	$(LN) . $(PACKAGE)-$(VERSION)
	@$(TAR) $(PACKAGE)-$(VERSION).tar.gz \
		$(PACKAGE)-$(VERSION)/src/ctype.c \
		$(PACKAGE)-$(VERSION)/src/dirent.c \
		$(PACKAGE)-$(VERSION)/src/errno.c \
		$(PACKAGE)-$(VERSION)/src/fcntl.c \
		$(PACKAGE)-$(VERSION)/src/grp.c \
		$(PACKAGE)-$(VERSION)/src/libgen.c \
		$(PACKAGE)-$(VERSION)/src/pwd.c \
		$(PACKAGE)-$(VERSION)/src/signal.c \
		$(PACKAGE)-$(VERSION)/src/stdlib.c \
		$(PACKAGE)-$(VERSION)/src/stdio.c \
		$(PACKAGE)-$(VERSION)/src/string.c \
		$(PACKAGE)-$(VERSION)/src/strings.c \
		$(PACKAGE)-$(VERSION)/src/stropts.c \
		$(PACKAGE)-$(VERSION)/src/sys/mman.c \
		$(PACKAGE)-$(VERSION)/src/sys/resource.c \
		$(PACKAGE)-$(VERSION)/src/sys/select.c \
		$(PACKAGE)-$(VERSION)/src/sys/stat.c \
		$(PACKAGE)-$(VERSION)/src/sys/statvfs.c \
		$(PACKAGE)-$(VERSION)/src/sys/time.c \
		$(PACKAGE)-$(VERSION)/src/sys/times.c \
		$(PACKAGE)-$(VERSION)/src/sys/utsname.c \
		$(PACKAGE)-$(VERSION)/src/sys/wait.c \
		$(PACKAGE)-$(VERSION)/src/syscalls.S \
		$(PACKAGE)-$(VERSION)/src/termios.c \
		$(PACKAGE)-$(VERSION)/src/time.c \
		$(PACKAGE)-$(VERSION)/src/unistd.c \
		$(PACKAGE)-$(VERSION)/src/utime.c \
		$(PACKAGE)-$(VERSION)/src/utmpx.c \
		$(PACKAGE)-$(VERSION)/src/start.S \
		$(PACKAGE)-$(VERSION)/src/Makefile \
		$(PACKAGE)-$(VERSION)/src/syscalls.h \
		$(PACKAGE)-$(VERSION)/src/project.conf \
		$(PACKAGE)-$(VERSION)/src/kernel/linux/Makefile \
		$(PACKAGE)-$(VERSION)/src/kernel/linux/common.h \
		$(PACKAGE)-$(VERSION)/src/kernel/linux/project.conf \
		$(PACKAGE)-$(VERSION)/src/kernel/linux/i386/Makefile \
		$(PACKAGE)-$(VERSION)/src/kernel/linux/i386/start.S \
		$(PACKAGE)-$(VERSION)/src/kernel/linux/i386/syscalls.S \
		$(PACKAGE)-$(VERSION)/src/kernel/linux/i386/project.conf \
		$(PACKAGE)-$(VERSION)/src/kernel/linux/sparc/Makefile \
		$(PACKAGE)-$(VERSION)/src/kernel/linux/sparc/start.S \
		$(PACKAGE)-$(VERSION)/src/kernel/linux/sparc/syscalls.S \
		$(PACKAGE)-$(VERSION)/src/kernel/linux/sparc/project.conf \
		$(PACKAGE)-$(VERSION)/src/kernel/netbsd/Makefile \
		$(PACKAGE)-$(VERSION)/src/kernel/netbsd/common.h \
		$(PACKAGE)-$(VERSION)/src/kernel/netbsd/common.S \
		$(PACKAGE)-$(VERSION)/src/kernel/netbsd/start.S \
		$(PACKAGE)-$(VERSION)/src/kernel/netbsd/sys/sysctl.h \
		$(PACKAGE)-$(VERSION)/src/kernel/netbsd/project.conf \
		$(PACKAGE)-$(VERSION)/src/kernel/netbsd/i386/Makefile \
		$(PACKAGE)-$(VERSION)/src/kernel/netbsd/i386/start.S \
		$(PACKAGE)-$(VERSION)/src/kernel/netbsd/i386/syscalls.S \
		$(PACKAGE)-$(VERSION)/src/kernel/netbsd/i386/project.conf \
		$(PACKAGE)-$(VERSION)/src/kernel/netbsd/sparc/Makefile \
		$(PACKAGE)-$(VERSION)/src/kernel/netbsd/sparc/start.S \
		$(PACKAGE)-$(VERSION)/src/kernel/netbsd/sparc/syscalls.S \
		$(PACKAGE)-$(VERSION)/src/kernel/netbsd/sparc/project.conf \
		$(PACKAGE)-$(VERSION)/src/kernel/netbsd/sparc64/Makefile \
		$(PACKAGE)-$(VERSION)/src/kernel/netbsd/sparc64/start.S \
		$(PACKAGE)-$(VERSION)/src/kernel/netbsd/sparc64/project.conf \
		$(PACKAGE)-$(VERSION)/include/Makefile \
		$(PACKAGE)-$(VERSION)/include/assert.h \
		$(PACKAGE)-$(VERSION)/include/ctype.h \
		$(PACKAGE)-$(VERSION)/include/dirent.h \
		$(PACKAGE)-$(VERSION)/include/errno.h \
		$(PACKAGE)-$(VERSION)/include/fcntl.h \
		$(PACKAGE)-$(VERSION)/include/grp.h \
		$(PACKAGE)-$(VERSION)/include/inttypes.h \
		$(PACKAGE)-$(VERSION)/include/libgen.h \
		$(PACKAGE)-$(VERSION)/include/limits.h \
		$(PACKAGE)-$(VERSION)/include/pwd.h \
		$(PACKAGE)-$(VERSION)/include/signal.h \
		$(PACKAGE)-$(VERSION)/include/stdarg.h \
		$(PACKAGE)-$(VERSION)/include/stddef.h \
		$(PACKAGE)-$(VERSION)/include/stdint.h \
		$(PACKAGE)-$(VERSION)/include/stdio.h \
		$(PACKAGE)-$(VERSION)/include/stdlib.h \
		$(PACKAGE)-$(VERSION)/include/string.h \
		$(PACKAGE)-$(VERSION)/include/strings.h \
		$(PACKAGE)-$(VERSION)/include/stropts.h \
		$(PACKAGE)-$(VERSION)/include/sys/ioctl.h \
		$(PACKAGE)-$(VERSION)/include/sys/mman.h \
		$(PACKAGE)-$(VERSION)/include/sys/resource.h \
		$(PACKAGE)-$(VERSION)/include/sys/select.h \
		$(PACKAGE)-$(VERSION)/include/sys/stat.h \
		$(PACKAGE)-$(VERSION)/include/sys/statvfs.h \
		$(PACKAGE)-$(VERSION)/include/sys/time.h \
		$(PACKAGE)-$(VERSION)/include/sys/times.h \
		$(PACKAGE)-$(VERSION)/include/sys/types.h \
		$(PACKAGE)-$(VERSION)/include/sys/utsname.h \
		$(PACKAGE)-$(VERSION)/include/sys/wait.h \
		$(PACKAGE)-$(VERSION)/include/termios.h \
		$(PACKAGE)-$(VERSION)/include/time.h \
		$(PACKAGE)-$(VERSION)/include/unistd.h \
		$(PACKAGE)-$(VERSION)/include/utime.h \
		$(PACKAGE)-$(VERSION)/include/utmpx.h \
		$(PACKAGE)-$(VERSION)/include/project.conf \
		$(PACKAGE)-$(VERSION)/include/compat/Makefile \
		$(PACKAGE)-$(VERSION)/include/compat/dirent.h \
		$(PACKAGE)-$(VERSION)/include/compat/errno.h \
		$(PACKAGE)-$(VERSION)/include/compat/fcntl.h \
		$(PACKAGE)-$(VERSION)/include/compat/limits.h \
		$(PACKAGE)-$(VERSION)/include/compat/signal.h \
		$(PACKAGE)-$(VERSION)/include/compat/sys/ioctl.h \
		$(PACKAGE)-$(VERSION)/include/compat/sys/mman.h \
		$(PACKAGE)-$(VERSION)/include/compat/sys/resource.h \
		$(PACKAGE)-$(VERSION)/include/compat/sys/stat.h \
		$(PACKAGE)-$(VERSION)/include/compat/sys/time.h \
		$(PACKAGE)-$(VERSION)/include/compat/sys/times.h \
		$(PACKAGE)-$(VERSION)/include/compat/sys/types.h \
		$(PACKAGE)-$(VERSION)/include/compat/sys/utsname.h \
		$(PACKAGE)-$(VERSION)/include/compat/termios.h \
		$(PACKAGE)-$(VERSION)/include/compat/time.h \
		$(PACKAGE)-$(VERSION)/include/compat/utmpx.h \
		$(PACKAGE)-$(VERSION)/include/compat/project.conf \
		$(PACKAGE)-$(VERSION)/include/kernel/linux/Makefile \
		$(PACKAGE)-$(VERSION)/include/kernel/linux/dirent.h \
		$(PACKAGE)-$(VERSION)/include/kernel/linux/errno.h \
		$(PACKAGE)-$(VERSION)/include/kernel/linux/fcntl.h \
		$(PACKAGE)-$(VERSION)/include/kernel/linux/limits.h \
		$(PACKAGE)-$(VERSION)/include/kernel/linux/signal.h \
		$(PACKAGE)-$(VERSION)/include/kernel/linux/sys/ioctl.h \
		$(PACKAGE)-$(VERSION)/include/kernel/linux/sys/mman.h \
		$(PACKAGE)-$(VERSION)/include/kernel/linux/sys/resource.h \
		$(PACKAGE)-$(VERSION)/include/kernel/linux/sys/stat.h \
		$(PACKAGE)-$(VERSION)/include/kernel/linux/sys/time.h \
		$(PACKAGE)-$(VERSION)/include/kernel/linux/sys/times.h \
		$(PACKAGE)-$(VERSION)/include/kernel/linux/sys/types.h \
		$(PACKAGE)-$(VERSION)/include/kernel/linux/sys/utsname.h \
		$(PACKAGE)-$(VERSION)/include/kernel/linux/termios.h \
		$(PACKAGE)-$(VERSION)/include/kernel/linux/time.h \
		$(PACKAGE)-$(VERSION)/include/kernel/linux/utmpx.h \
		$(PACKAGE)-$(VERSION)/include/kernel/linux/project.conf \
		$(PACKAGE)-$(VERSION)/include/kernel/netbsd/Makefile \
		$(PACKAGE)-$(VERSION)/include/kernel/netbsd/dirent.h \
		$(PACKAGE)-$(VERSION)/include/kernel/netbsd/errno.h \
		$(PACKAGE)-$(VERSION)/include/kernel/netbsd/fcntl.h \
		$(PACKAGE)-$(VERSION)/include/kernel/netbsd/limits.h \
		$(PACKAGE)-$(VERSION)/include/kernel/netbsd/signal.h \
		$(PACKAGE)-$(VERSION)/include/kernel/netbsd/sys/ioctl.h \
		$(PACKAGE)-$(VERSION)/include/kernel/netbsd/sys/mman.h \
		$(PACKAGE)-$(VERSION)/include/kernel/netbsd/sys/resource.h \
		$(PACKAGE)-$(VERSION)/include/kernel/netbsd/sys/stat.h \
		$(PACKAGE)-$(VERSION)/include/kernel/netbsd/sys/time.h \
		$(PACKAGE)-$(VERSION)/include/kernel/netbsd/sys/times.h \
		$(PACKAGE)-$(VERSION)/include/kernel/netbsd/sys/types.h \
		$(PACKAGE)-$(VERSION)/include/kernel/netbsd/sys/utsname.h \
		$(PACKAGE)-$(VERSION)/include/kernel/netbsd/termios.h \
		$(PACKAGE)-$(VERSION)/include/kernel/netbsd/time.h \
		$(PACKAGE)-$(VERSION)/include/kernel/netbsd/utmpx.h \
		$(PACKAGE)-$(VERSION)/include/kernel/netbsd/project.conf \
		$(PACKAGE)-$(VERSION)/include/kernel/solaris/Makefile \
		$(PACKAGE)-$(VERSION)/include/kernel/solaris/errno.h \
		$(PACKAGE)-$(VERSION)/include/kernel/solaris/sys/mman.h \
		$(PACKAGE)-$(VERSION)/include/kernel/solaris/sys/stat.h \
		$(PACKAGE)-$(VERSION)/include/kernel/solaris/sys/time.h \
		$(PACKAGE)-$(VERSION)/include/kernel/solaris/sys/times.h \
		$(PACKAGE)-$(VERSION)/include/kernel/solaris/sys/types.h \
		$(PACKAGE)-$(VERSION)/include/kernel/solaris/sys/utsname.h \
		$(PACKAGE)-$(VERSION)/include/kernel/solaris/time.h \
		$(PACKAGE)-$(VERSION)/include/kernel/solaris/project.conf \
		$(PACKAGE)-$(VERSION)/Makefile \
		$(PACKAGE)-$(VERSION)/COPYING \
		$(PACKAGE)-$(VERSION)/project.conf
	$(RM) $(PACKAGE)-$(VERSION)

install: all
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) install) || exit; done

uninstall:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) uninstall) || exit; done

.PHONY: all subdirs clean distclean dist install uninstall
