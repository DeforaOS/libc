SUBDIRS	= dl kernel/linux kernel/freebsd kernel/netbsd kernel/openbsd kernel/solaris socket
TARGETS	= libc.a libc.so start.o
PREFIX	= /usr/local
DESTDIR	= 
LIBDIR	= $(PREFIX)/lib
CC	= cc
CPPFLAGSF= -nostdinc -I ../include
CPPFLAGS=
CFLAGSF	= -W
CFLAGS	= -Wall -g -ansi -ffreestanding
AS	= $(CC)
ASFLAGS	= -W -Wall -g -ansi -c
AR	= ar -rc
RANLIB	= ranlib
LD	= $(CC) -shared
RM	= rm -f
MKDIR	= mkdir -p
INSTALL	= install


all: subdirs $(TARGETS)

subdirs:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE)) || exit; done

libc_OBJS = ctype.o dirent.o errno.o fcntl.o float.o fnmatch.o grp.o libgen.o math.o poll.o pwd.o signal.o stdlib.o stdio.o string.o strings.o stropts.o sys/mman.o sys/mount.o sys/reboot.o sys/resource.o sys/select.o sys/stat.o sys/statvfs.o sys/time.o sys/times.o sys/utsname.o sys/wait.o syscalls.o termios.o time.o unistd.o utime.o utmpx.o
libc_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
libc_ASFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(ASFLAGS)

libc.a: $(libc_OBJS)
	$(AR) libc.a $(libc_OBJS)
	$(RANLIB) libc.a

libc.so: $(libc_OBJS)
	$(LD) -o libc.so $(libc_OBJS)

start.o_OBJS = start.o
start.o_ASFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(ASFLAGS)

ctype.o: ctype.c
	$(CC) $(libc_CFLAGS) -c ctype.c

dirent.o: dirent.c
	$(CC) $(libc_CFLAGS) -c dirent.c

errno.o: errno.c
	$(CC) $(libc_CFLAGS) -c errno.c

fcntl.o: fcntl.c syscalls.h
	$(CC) $(libc_CFLAGS) -c fcntl.c

float.o: float.c
	$(CC) $(libc_CFLAGS) -c float.c

fnmatch.o: fnmatch.c
	$(CC) $(libc_CFLAGS) -c fnmatch.c

grp.o: grp.c
	$(CC) $(libc_CFLAGS) -c grp.c

libgen.o: libgen.c
	$(CC) $(libc_CFLAGS) -c libgen.c

math.o: math.c
	$(CC) $(libc_CFLAGS) -c math.c

poll.o: poll.c
	$(CC) $(libc_CFLAGS) -c poll.c

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
	$(CC) $(libc_CFLAGS) -o sys/mman.o -c sys/mman.c

sys/mount.o: sys/mount.c syscalls.h
	$(CC) $(libc_CFLAGS) -o sys/mount.o -c sys/mount.c

sys/reboot.o: sys/reboot.c
	$(CC) $(libc_CFLAGS) -o sys/reboot.o -c sys/reboot.c

sys/resource.o: sys/resource.c syscalls.h
	$(CC) $(libc_CFLAGS) -o sys/resource.o -c sys/resource.c

sys/select.o: sys/select.c
	$(CC) $(libc_CFLAGS) -o sys/select.o -c sys/select.c

sys/stat.o: sys/stat.c syscalls.h
	$(CC) $(libc_CFLAGS) -o sys/stat.o -c sys/stat.c

sys/statvfs.o: sys/statvfs.c syscalls.h
	$(CC) $(libc_CFLAGS) -o sys/statvfs.o -c sys/statvfs.c

sys/time.o: sys/time.c
	$(CC) $(libc_CFLAGS) -o sys/time.o -c sys/time.c

sys/times.o: sys/times.c syscalls.h
	$(CC) $(libc_CFLAGS) -o sys/times.o -c sys/times.c

sys/utsname.o: sys/utsname.c
	$(CC) $(libc_CFLAGS) -o sys/utsname.o -c sys/utsname.c

sys/wait.o: sys/wait.c syscalls.h
	$(CC) $(libc_CFLAGS) -o sys/wait.o -c sys/wait.c

syscalls.o: syscalls.S kernel/freebsd/common.h kernel/freebsd/i386/syscalls.S kernel/linux/common.h kernel/linux/arm/syscalls.S kernel/linux/i386/syscalls.S kernel/linux/sparc/syscalls.S kernel/netbsd/common.h kernel/netbsd/common.S kernel/netbsd/amd64/syscalls.S kernel/netbsd/i386/syscalls.S kernel/netbsd/sparc/syscalls.S kernel/netbsd/sparc64/syscalls.S kernel/openbsd/common.h kernel/openbsd/arm/syscalls.S kernel/openbsd/i386/syscalls.S
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

start.o: start.S kernel/freebsd/i386/start.S kernel/linux/arm/start.S kernel/linux/i386/start.S kernel/linux/sparc/start.S kernel/netbsd/amd64/start.S kernel/netbsd/i386/start.S kernel/netbsd/sparc64/start.S kernel/netbsd/sparc/start.S kernel/openbsd/arm/start.S kernel/openbsd/i386/start.S
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
	$(MKDIR) $(DESTDIR)$(LIBDIR)
	$(INSTALL) -m 0644 start.o $(DESTDIR)$(LIBDIR)/start.o

uninstall:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) uninstall) || exit; done
	$(RM) $(DESTDIR)$(LIBDIR)/libc.a
	$(RM) $(DESTDIR)$(LIBDIR)/libc.so
	$(RM) $(DESTDIR)$(LIBDIR)/start.o

.PHONY: all subdirs clean distclean install uninstall
