SUBDIRS	= kernel/linux kernel/freebsd kernel/netbsd kernel/openbsd kernel/solaris
TARGETS	= libc.a libc.so start.o
PREFIX	= /usr/local
DESTDIR	= 
LIBDIR	= $(PREFIX)/lib
CC	= cc
CPPFLAGS= -I ../include -nostdinc
CFLAGSF	= -W
CFLAGS	= -Wall -g -ansi
AS	= $(CC)
ASFLAGS	= -W -Wall -g -ansi -c
AR	= ar -rc
RANLIB	= ranlib
LD	= ld -shared
RM	= rm -f
MKDIR	= mkdir -p
INSTALL	= install


all: subdirs $(TARGETS)

subdirs:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE)) || exit; done

libc_OBJS = ctype.o dirent.o errno.o fcntl.o fnmatch.o grp.o libgen.o pwd.o signal.o stdlib.o stdio.o string.o strings.o stropts.o sys/mman.o sys/mount.o sys/reboot.o sys/resource.o sys/select.o sys/stat.o sys/statvfs.o sys/time.o sys/times.o sys/utsname.o sys/wait.o syscalls.o termios.o time.o unistd.o utime.o utmpx.o
libc_CFLAGS = $(CPPFLAGS) $(CFLAGSF) $(CFLAGS) -fPIC
libc_ASFLAGS = $(CPPFLAGS) $(ASFLAGS)

libc.a: $(libc_OBJS)
	$(AR) libc.a $(libc_OBJS)
	$(RANLIB) libc.a

libc.so: $(libc_OBJS)
	$(LD) -o libc.so $(libc_OBJS)

start.o_OBJS = start.o
start.o_ASFLAGS = $(CPPFLAGS) $(ASFLAGS)

ctype.o: ctype.c
	$(CC) $(libc_CFLAGS) -c ctype.c

dirent.o: dirent.c
	$(CC) $(libc_CFLAGS) -c dirent.c

errno.o: errno.c
	$(CC) $(libc_CFLAGS) -c errno.c

fcntl.o: fcntl.c syscalls.h
	$(CC) $(libc_CFLAGS) -c fcntl.c

fnmatch.o: fnmatch.c
	$(CC) $(libc_CFLAGS) -c fnmatch.c

grp.o: grp.c
	$(CC) $(libc_CFLAGS) -c grp.c

libgen.o: libgen.c
	$(CC) $(libc_CFLAGS) -c libgen.c

pwd.o: pwd.c
	$(CC) $(libc_CFLAGS) -c pwd.c

signal.o: signal.c
	$(CC) $(libc_CFLAGS) -c signal.c

stdlib.o: stdlib.c
	$(CC) $(libc_CFLAGS) -c stdlib.c

stdio.o: stdio.c
	$(CC) $(libc_CFLAGS) -c stdio.c

string.o: string.c
	$(CC) $(libc_CFLAGS) -c string.c

strings.o: strings.c
	$(CC) $(libc_CFLAGS) -c strings.c

stropts.o: stropts.c
	$(CC) $(libc_CFLAGS) -c stropts.c

sys/mman.o: sys/mman.c syscalls.h
	$(CC) $(libc_CFLAGS) -c sys/mman.c -o sys/mman.o

sys/mount.o: sys/mount.c syscalls.h
	$(CC) $(libc_CFLAGS) -c sys/mount.c -o sys/mount.o

sys/reboot.o: sys/reboot.c
	$(CC) $(libc_CFLAGS) -c sys/reboot.c -o sys/reboot.o

sys/resource.o: sys/resource.c syscalls.h
	$(CC) $(libc_CFLAGS) -c sys/resource.c -o sys/resource.o

sys/select.o: sys/select.c
	$(CC) $(libc_CFLAGS) -c sys/select.c -o sys/select.o

sys/stat.o: sys/stat.c syscalls.h
	$(CC) $(libc_CFLAGS) -c sys/stat.c -o sys/stat.o

sys/statvfs.o: sys/statvfs.c syscalls.h
	$(CC) $(libc_CFLAGS) -c sys/statvfs.c -o sys/statvfs.o

sys/time.o: sys/time.c
	$(CC) $(libc_CFLAGS) -c sys/time.c -o sys/time.o

sys/times.o: sys/times.c syscalls.h
	$(CC) $(libc_CFLAGS) -c sys/times.c -o sys/times.o

sys/utsname.o: sys/utsname.c
	$(CC) $(libc_CFLAGS) -c sys/utsname.c -o sys/utsname.o

sys/wait.o: sys/wait.c syscalls.h
	$(CC) $(libc_CFLAGS) -c sys/wait.c -o sys/wait.o

syscalls.o: syscalls.S common.h kernel/linux/common.h kernel/linux/i386/syscalls.S kernel/linux/sparc/syscalls.S kernel/freebsd/common.h kernel/freebsd/i386/syscalls.S kernel/netbsd/common.h kernel/netbsd/common.S kernel/netbsd/amd64/syscalls.S kernel/netbsd/i386/syscalls.S kernel/netbsd/sparc/syscalls.S ../config.h
	$(AS) $(libc_ASFLAGS) -o syscalls.o syscalls.S

termios.o: termios.c syscalls.h
	$(CC) $(libc_CFLAGS) -c termios.c

time.o: time.c
	$(CC) $(libc_CFLAGS) -c time.c

unistd.o: unistd.c syscalls.h
	$(CC) $(libc_CFLAGS) -c unistd.c

utime.o: utime.c
	$(CC) $(libc_CFLAGS) -c utime.c

utmpx.o: utmpx.c
	$(CC) $(libc_CFLAGS) -c utmpx.c

start.o: start.S common.h kernel/linux/i386/start.S kernel/linux/sparc/start.S kernel/netbsd/amd64/start.S kernel/netbsd/i386/start.S kernel/netbsd/sparc64/start.S kernel/netbsd/sparc/start.S ../config.h
	$(AS) $(start.o_ASFLAGS) -o start.o start.S

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
