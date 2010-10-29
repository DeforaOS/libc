SUBDIRS	= dl kernel/linux kernel/freebsd kernel/netbsd kernel/openbsd kernel/solaris math pthread socket
TARGETS	= libc.a libc.so start.o
PREFIX	= /usr/local
DESTDIR	= 
LIBDIR	= $(PREFIX)/lib
AS	= $(CC)
ASFLAGS	= -W -fPIC -Wall -g -pedantic -ffreestanding -c
CC	= cc
CPPFLAGSF= -nostdinc -isystem ../include -DPIC
CPPFLAGS=
CFLAGSF	= -W -fPIC
CFLAGS	= -Wall -g -pedantic -ffreestanding
AR	= ar -rc
RANLIB	= ranlib
LD	= $(CC) -nostdlib -shared
BINDIR	= $(PREFIX)/bin
RM	= rm -f
LN	= ln -f
MKDIR	= mkdir -p
INSTALL	= install


all: subdirs $(TARGETS)

subdirs:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE)) || exit; done

libc_OBJS = ctype.o dirent.o errno.o fcntl.o float.o fnmatch.o grp.o iconv.o langinfo.o libgen.o locale.o poll.o pwd.o search.o setjmp.o signal.o stdlib.o stdio.o string.o strings.o stropts.o sys/ipc.o sys/mman.o sys/mount.o sys/reboot.o sys/resource.o sys/select.o sys/shm.o sys/stat.o sys/statvfs.o sys/time.o sys/times.o sys/utsname.o sys/wait.o syscalls.o syslog.o termios.o time.o ucontext.o unistd.o utime.o utmpx.o
libc_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
libc_LDFLAGS = $(LDFLAGSF) $(LDFLAGS) `$(CC) -print-libgcc-file-name`
libc_ASFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(ASFLAGS)

libc.a: $(libc_OBJS)
	$(AR) libc.a $(libc_OBJS)
	$(RANLIB) libc.a

libc.so: $(libc_OBJS)
	$(LD) -o libc.so -Wl,-soname,libc.so.0 $(libc_OBJS) `$(CC) -print-libgcc-file-name`

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

iconv.o: iconv.c
	$(CC) $(libc_CFLAGS) -c iconv.c

langinfo.o: langinfo.c
	$(CC) $(libc_CFLAGS) -c langinfo.c

libgen.o: libgen.c
	$(CC) $(libc_CFLAGS) -c libgen.c

locale.o: locale.c
	$(CC) $(libc_CFLAGS) -c locale.c

poll.o: poll.c
	$(CC) $(libc_CFLAGS) -c poll.c

pwd.o: pwd.c
	$(CC) $(libc_CFLAGS) -c pwd.c

search.o: search.c
	$(CC) $(libc_CFLAGS) -c search.c

setjmp.o: setjmp.c
	$(CC) $(libc_CFLAGS) -c setjmp.c

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

sys/ipc.o: sys/ipc.c syscalls.h
	$(CC) $(libc_CFLAGS) -o sys/ipc.o -c sys/ipc.c

sys/mman.o: sys/mman.c syscalls.h
	$(CC) $(libc_CFLAGS) -o sys/mman.o -c sys/mman.c

sys/mount.o: sys/mount.c syscalls.h
	$(CC) $(libc_CFLAGS) -o sys/mount.o -c sys/mount.c

sys/reboot.o: sys/reboot.c
	$(CC) $(libc_CFLAGS) -o sys/reboot.o -c sys/reboot.c

sys/resource.o: sys/resource.c syscalls.h
	$(CC) $(libc_CFLAGS) -o sys/resource.o -c sys/resource.c

sys/select.o: sys/select.c syscalls.h
	$(CC) $(libc_CFLAGS) -o sys/select.o -c sys/select.c

sys/shm.o: sys/shm.c syscalls.h
	$(CC) $(libc_CFLAGS) -o sys/shm.o -c sys/shm.c

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

syscalls.o: syscalls.S kernel/freebsd/common.h kernel/freebsd/i386/syscalls.S kernel/linux/common.h kernel/linux/amd64/syscalls.S kernel/linux/arm/syscalls.S kernel/linux/i386/syscalls.S kernel/linux/sparc/syscalls.S kernel/netbsd/common.h kernel/netbsd/common.S kernel/netbsd/amd64/syscalls.S kernel/netbsd/i386/syscalls.S kernel/netbsd/sparc/syscalls.S kernel/netbsd/sparc64/syscalls.S kernel/openbsd/common.h kernel/openbsd/arm/syscalls.S kernel/openbsd/i386/syscalls.S
	$(AS) $(libc_ASFLAGS) -o syscalls.o syscalls.S

syslog.o: syslog.c
	$(CC) $(libc_CFLAGS) -c syslog.c

termios.o: termios.c syscalls.h
	$(CC) $(libc_CFLAGS) -c termios.c

time.o: time.c
	$(CC) $(libc_CFLAGS) -c time.c

ucontext.o: ucontext.c syscalls.h
	$(CC) $(libc_CFLAGS) -c ucontext.c

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
	$(RM) -- $(libc_OBJS) $(start.o_OBJS)

distclean:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) distclean) || exit; done
	$(RM) -- $(libc_OBJS) $(start.o_OBJS)
	$(RM) -- $(TARGETS)

install: all
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) install) || exit; done
	$(MKDIR) $(DESTDIR)$(LIBDIR)
	$(INSTALL) -m 0644 -- libc.a $(DESTDIR)$(LIBDIR)/libc.a
	$(INSTALL) -m 0755 -- libc.so $(DESTDIR)$(LIBDIR)/libc.so.0.0
	$(LN) -s -- libc.so.0.0 $(DESTDIR)$(LIBDIR)/libc.so.0
	$(LN) -s -- libc.so.0.0 $(DESTDIR)$(LIBDIR)/libc.so
	$(MKDIR) $(DESTDIR)$(LIBDIR)
	$(INSTALL) -m 0644 -- start.o $(DESTDIR)$(LIBDIR)/start.o

uninstall:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) uninstall) || exit; done
	$(RM) -- $(DESTDIR)$(LIBDIR)/libc.a
	$(RM) -- $(DESTDIR)$(LIBDIR)/libc.so.0.0
	$(RM) -- $(DESTDIR)$(LIBDIR)/libc.so.0
	$(RM) -- $(DESTDIR)$(LIBDIR)/libc.so
	$(RM) -- $(DESTDIR)$(LIBDIR)/start.o

.PHONY: all subdirs clean distclean install uninstall
