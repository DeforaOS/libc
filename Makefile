PACKAGE	= libc
VERSION	= 0.0.0
SUBDIRS	= src include
TAR	= tar cfzv


all: subdirs

subdirs:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE)) || exit; done

clean:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) clean) || exit; done

distclean:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) distclean) || exit; done

dist: distclean
	@$(TAR) $(PACKAGE)-$(VERSION).tar.gz \
		include/assert.h \
		include/ctype.h \
		include/dirent.h \
		include/errno.h \
		include/fcntl.h \
		include/grp.h \
		include/inttypes.h \
		include/libgen.h \
		include/limits.h \
		include/pwd.h \
		include/signal.h \
		include/stdarg.h \
		include/stddef.h \
		include/stdint.h \
		include/stdio.h \
		include/stdlib.h \
		include/string.h \
		include/sys/mman.h \
		include/sys/stat.h \
		include/sys/times.h \
		include/sys/types.h \
		include/sys/utsname.h \
		include/sys/wait.h \
		include/time.h \
		include/unistd.h \
		include/utime.h \
		include/project.conf \
		include/Makefile \
		src/ctype.c \
		src/dirent.c \
		src/errno.c \
		src/fcntl.c \
		src/grp.c \
		src/libgen.c \
		src/pwd.c \
		src/signal.c \
		src/stdlib.c \
		src/stdio.c \
		src/string.c \
		src/sys/mman.c \
		src/sys/stat.c \
		src/sys/times.c \
		src/sys/utsname.c \
		src/sys/wait.c \
		src/syscalls.S \
		src/time.c \
		src/unistd.c \
		src/utime.c \
		src/syscalls.h \
		src/project.conf \
		src/Makefile \
		project.conf \
		Makefile

install: all
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) install) || exit; done

uninstall:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) uninstall) || exit; done
