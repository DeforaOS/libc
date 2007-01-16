SUBDIRS	= kernel/linux kernel/netbsd
TARGETS	= libc.a libc.so start.o
PREFIX	= /usr/local
DESTDIR	= 
LIBDIR	= $(PREFIX)/lib
CC	= cc
CPPFLAGS=
CFLAGSF	= -W -I ../include
CFLAGS	= -Wall -nostdinc -fPIC -g -ansi
AR	= ar -rc
RANLIB	= ranlib
LD	= ld -shared
RM	= rm -f
MKDIR	= mkdir -p
INSTALL	= install


all: subdirs $(TARGETS)

subdirs:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE)) || exit; done

libc_OBJS = ctype.o dirent.o errno.o fcntl.o grp.o kernel/netbsd/compat.o libgen.o pwd.o signal.o stdlib.o stdio.o string.o sys/mman.o sys/select.o sys/stat.o sys/statvfs.o sys/time.o sys/times.o sys/utsname.o sys/wait.o syscalls.o time.o unistd.o utime.o utmpx.o
libc_CFLAGS = $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)

libc.a: $(libc_OBJS)
	$(AR) libc.a $(libc_OBJS)
	$(RANLIB) libc.a

libc.so: $(libc_OBJS)
	$(LD) -o libc.so $(libc_OBJS)

start.o_OBJS = start.o
start.o_CFLAGS = $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)

ctype.o: ctype.c
	$(CC) $(libc_CFLAGS) -c ctype.c

dirent.o: dirent.c syscalls.h
	$(CC) $(libc_CFLAGS) -c dirent.c

errno.o: errno.c
	$(CC) $(libc_CFLAGS) -c errno.c

fcntl.o: fcntl.c syscalls.h
	$(CC) $(libc_CFLAGS) -c fcntl.c

grp.o: grp.c
	$(CC) $(libc_CFLAGS) -c grp.c

kernel/netbsd/compat.o: kernel/netbsd/compat.c
	$(CC) $(libc_CFLAGS) -c kernel/netbsd/compat.c -o kernel/netbsd/compat.o

libgen.o: libgen.c
	$(CC) $(libc_CFLAGS) -c libgen.c

pwd.o: pwd.c
	$(CC) $(libc_CFLAGS) -c pwd.c

signal.o: signal.c syscalls.h
	$(CC) $(libc_CFLAGS) -c signal.c

stdlib.o: stdlib.c
	$(CC) $(libc_CFLAGS) -c stdlib.c

stdio.o: stdio.c syscalls.h
	$(CC) $(libc_CFLAGS) -c stdio.c

string.o: string.c
	$(CC) $(libc_CFLAGS) -c string.c

sys/mman.o: sys/mman.c syscalls.h
	$(CC) $(libc_CFLAGS) -c sys/mman.c -o sys/mman.o

sys/select.o: sys/select.c syscalls.h
	$(CC) $(libc_CFLAGS) -c sys/select.c -o sys/select.o

sys/stat.o: sys/stat.c syscalls.h
	$(CC) $(libc_CFLAGS) -c sys/stat.c -o sys/stat.o

sys/statvfs.o: sys/statvfs.c syscalls.h
	$(CC) $(libc_CFLAGS) -c sys/statvfs.c -o sys/statvfs.o

sys/time.o: sys/time.c syscalls.h
	$(CC) $(libc_CFLAGS) -c sys/time.c -o sys/time.o

sys/times.o: sys/times.c syscalls.h
	$(CC) $(libc_CFLAGS) -c sys/times.c -o sys/times.o

sys/utsname.o: sys/utsname.c syscalls.h
	$(CC) $(libc_CFLAGS) -c sys/utsname.c -o sys/utsname.o

sys/wait.o: sys/wait.c syscalls.h
	$(CC) $(libc_CFLAGS) -c sys/wait.c -o sys/wait.o

syscalls.o: syscalls.S
	$(CC) $(libc_CFLAGS) -c syscalls.S

time.o: time.c syscalls.h
	$(CC) $(libc_CFLAGS) -c time.c

unistd.o: unistd.c syscalls.h
	$(CC) $(libc_CFLAGS) -c unistd.c

utime.o: utime.c syscalls.h
	$(CC) $(libc_CFLAGS) -c utime.c

utmpx.o: utmpx.c
	$(CC) $(libc_CFLAGS) -c utmpx.c

start.o: start.S kernel/linux/i386/start.S kernel/linux/sparc/start.S kernel/netbsd/i386/start.S kernel/netbsd/sparc/start.S
	$(CC) $(start.o_CFLAGS) -c start.S

clean:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) clean) || exit; done
	$(RM) $(libc_OBJS) $(start.o_OBJS)

distclean:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) distclean) || exit; done
	$(RM) $(libc_OBJS) $(start.o_OBJS)
	$(RM) $(TARGETS)

install: all
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) install) || exit; done
	$(MKDIR) $(DESTDIR)$(LIBDIR)
	$(INSTALL) -m 0644 libc.a $(DESTDIR)$(LIBDIR)/libc.a
	$(INSTALL) -m 0755 libc.so $(DESTDIR)$(LIBDIR)/libc.so

uninstall:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) uninstall) || exit; done
	$(RM) $(DESTDIR)$(LIBDIR)/libc.a
	$(RM) $(DESTDIR)$(LIBDIR)/libc.so

.PHONY: all subdirs clean distclean install uninstall
