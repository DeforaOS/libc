SUBDIRS	= kernel/darwin kernel/freebsd kernel/linux kernel/netbsd kernel/openbsd kernel/solaris
TARGETS	= $(OBJDIR)libc.a $(OBJDIR)libc.so.0.0 $(OBJDIR)libc.so.0 $(OBJDIR)libc.so $(OBJDIR)start.o
OBJDIR	=
PREFIX	= /usr/local
DESTDIR	=
LIBDIR	= $(PREFIX)/lib
AS	= $(CC)
ASFLAGS	= -W -fPIC -Wall -g -pedantic -ffreestanding -c
CC	= cc
CPPFLAGSF= -nostdinc -isystem ../include -DPIC
CPPFLAGS=
CFLAGSF	= -W -fPIC
CFLAGS	= -Wall -g -O2 -pedantic -ffreestanding
LDFLAGSF= -nostdlib
AR	= ar
RANLIB	= ranlib
CCSHARED= $(CC) -shared
BINDIR	= $(PREFIX)/bin
SBINDIR	= $(PREFIX)/sbin
RM	= rm -f
LN	= ln -f
MKDIR	= mkdir -m 0755 -p
INSTALL	= install


all: subdirs $(TARGETS)

subdirs:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE)) || exit; done

libc_OBJS = $(OBJDIR)ctype.o $(OBJDIR)dirent.o $(OBJDIR)errno.o $(OBJDIR)fcntl.o $(OBJDIR)float.o $(OBJDIR)fnmatch.o $(OBJDIR)grp.o $(OBJDIR)iconv.o $(OBJDIR)langinfo.o $(OBJDIR)libgen.o $(OBJDIR)locale.o $(OBJDIR)net/if.o $(OBJDIR)poll.o $(OBJDIR)pwd.o $(OBJDIR)regex.o $(OBJDIR)search.o $(OBJDIR)setjmp.o $(OBJDIR)signal.o $(OBJDIR)stdlib.o $(OBJDIR)stdio.o $(OBJDIR)string.o $(OBJDIR)strings.o $(OBJDIR)stropts.o $(OBJDIR)sys/ipc.o $(OBJDIR)sys/mman.o $(OBJDIR)sys/mount.o $(OBJDIR)sys/ptrace.o $(OBJDIR)sys/reboot.o $(OBJDIR)sys/resource.o $(OBJDIR)sys/select.o $(OBJDIR)sys/shm.o $(OBJDIR)sys/stat.o $(OBJDIR)sys/statvfs.o $(OBJDIR)sys/time.o $(OBJDIR)sys/times.o $(OBJDIR)sys/utsname.o $(OBJDIR)sys/wait.o $(OBJDIR)syscalls.o $(OBJDIR)syslog.o $(OBJDIR)termios.o $(OBJDIR)time.o $(OBJDIR)ucontext.o $(OBJDIR)unistd.o $(OBJDIR)utime.o $(OBJDIR)utmpx.o $(OBJDIR)wchar.o
libc_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
libc_LDFLAGS = $(LDFLAGSF) $(LDFLAGS) `$(CC) -print-libgcc-file-name`
libc_ASFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(ASFLAGS)

$(OBJDIR)libc.a: $(libc_OBJS)
	$(AR) -rc $(OBJDIR)libc.a $(libc_OBJS)
	$(RANLIB) $(OBJDIR)libc.a

$(OBJDIR)libc.so.0.0 $(OBJDIR)libc.so.0 $(OBJDIR)libc.so: $(libc_OBJS)
	$(CCSHARED) -o $(OBJDIR)libc.so.0.0 -Wl,-soname,libc.so.0 $(libc_OBJS) $(libc_LDFLAGS)
	$(LN) -s -- libc.so.0.0 $(OBJDIR)libc.so.0
	$(LN) -s -- libc.so.0.0 $(OBJDIR)libc.so

start.o_OBJS = $(OBJDIR)start.o
start.o_ASFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(ASFLAGS)

$(OBJDIR)ctype.o: ctype.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)ctype.o -c ctype.c

$(OBJDIR)dirent.o: dirent.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)dirent.o -c dirent.c

$(OBJDIR)errno.o: errno.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)errno.o -c errno.c

$(OBJDIR)fcntl.o: fcntl.c syscalls.h
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)fcntl.o -c fcntl.c

$(OBJDIR)float.o: float.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)float.o -c float.c

$(OBJDIR)fnmatch.o: fnmatch.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)fnmatch.o -c fnmatch.c

$(OBJDIR)grp.o: grp.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)grp.o -c grp.c

$(OBJDIR)iconv.o: iconv.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)iconv.o -c iconv.c

$(OBJDIR)langinfo.o: langinfo.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)langinfo.o -c langinfo.c

$(OBJDIR)libgen.o: libgen.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)libgen.o -c libgen.c

$(OBJDIR)locale.o: locale.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)locale.o -c locale.c

$(OBJDIR)net/if.o: net/if.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)net/if.o -c net/if.c

$(OBJDIR)poll.o: poll.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)poll.o -c poll.c

$(OBJDIR)pwd.o: pwd.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)pwd.o -c pwd.c

$(OBJDIR)regex.o: regex.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)regex.o -c regex.c

$(OBJDIR)search.o: search.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)search.o -c search.c

$(OBJDIR)setjmp.o: setjmp.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)setjmp.o -c setjmp.c

$(OBJDIR)signal.o: signal.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)signal.o -c signal.c

$(OBJDIR)stdlib.o: stdlib.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)stdlib.o -c stdlib.c

$(OBJDIR)stdio.o: stdio.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)stdio.o -c stdio.c

$(OBJDIR)string.o: string.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)string.o -c string.c

$(OBJDIR)strings.o: strings.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)strings.o -c strings.c

$(OBJDIR)stropts.o: stropts.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)stropts.o -c stropts.c

$(OBJDIR)sys/ipc.o: sys/ipc.c syscalls.h
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)sys/ipc.o -c sys/ipc.c

$(OBJDIR)sys/mman.o: sys/mman.c syscalls.h
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)sys/mman.o -c sys/mman.c

$(OBJDIR)sys/mount.o: sys/mount.c syscalls.h
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)sys/mount.o -c sys/mount.c

$(OBJDIR)sys/ptrace.o: sys/ptrace.c syscalls.h
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)sys/ptrace.o -c sys/ptrace.c

$(OBJDIR)sys/reboot.o: sys/reboot.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)sys/reboot.o -c sys/reboot.c

$(OBJDIR)sys/resource.o: sys/resource.c syscalls.h
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)sys/resource.o -c sys/resource.c

$(OBJDIR)sys/select.o: sys/select.c syscalls.h
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)sys/select.o -c sys/select.c

$(OBJDIR)sys/shm.o: sys/shm.c syscalls.h
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)sys/shm.o -c sys/shm.c

$(OBJDIR)sys/stat.o: sys/stat.c syscalls.h
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)sys/stat.o -c sys/stat.c

$(OBJDIR)sys/statvfs.o: sys/statvfs.c syscalls.h
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)sys/statvfs.o -c sys/statvfs.c

$(OBJDIR)sys/time.o: sys/time.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)sys/time.o -c sys/time.c

$(OBJDIR)sys/times.o: sys/times.c syscalls.h
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)sys/times.o -c sys/times.c

$(OBJDIR)sys/utsname.o: sys/utsname.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)sys/utsname.o -c sys/utsname.c

$(OBJDIR)sys/wait.o: sys/wait.c syscalls.h
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)sys/wait.o -c sys/wait.c

$(OBJDIR)syscalls.o: syscalls.S kernel/darwin/amd64/syscalls.S kernel/freebsd/amd64/syscalls.S kernel/freebsd/i386/syscalls.S kernel/linux/amd64/syscalls.S kernel/linux/arm/syscalls.S kernel/linux/i386/syscalls.S kernel/linux/sparc/syscalls.S kernel/netbsd/common.S kernel/netbsd/amd64/syscalls.S kernel/netbsd/i386/syscalls.S kernel/netbsd/sparc/syscalls.S kernel/netbsd/sparc64/syscalls.S kernel/openbsd/arm/syscalls.S kernel/openbsd/i386/syscalls.S
	$(AS) $(libc_ASFLAGS) -o $(OBJDIR)syscalls.o syscalls.S

$(OBJDIR)syslog.o: syslog.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)syslog.o -c syslog.c

$(OBJDIR)termios.o: termios.c syscalls.h
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)termios.o -c termios.c

$(OBJDIR)time.o: time.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)time.o -c time.c

$(OBJDIR)ucontext.o: ucontext.c syscalls.h
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)ucontext.o -c ucontext.c

$(OBJDIR)unistd.o: unistd.c syscalls.h
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)unistd.o -c unistd.c

$(OBJDIR)utime.o: utime.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)utime.o -c utime.c

$(OBJDIR)utmpx.o: utmpx.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)utmpx.o -c utmpx.c

$(OBJDIR)wchar.o: wchar.c
	$(CC) $(libc_CFLAGS) -o $(OBJDIR)wchar.o -c wchar.c

$(OBJDIR)start.o: start.S kernel/freebsd/amd64/start.S kernel/freebsd/i386/start.S kernel/linux/arm/start.S kernel/linux/i386/start.S kernel/linux/sparc/start.S kernel/netbsd/amd64/start.S kernel/netbsd/i386/start.S kernel/netbsd/sparc64/start.S kernel/netbsd/sparc/start.S kernel/openbsd/arm/start.S kernel/openbsd/i386/start.S
	$(AS) $(start.o_ASFLAGS) -o $(OBJDIR)start.o start.S

clean:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) clean) || exit; done
	$(RM) -- $(libc_OBJS) $(start.o_OBJS)

distclean:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) distclean) || exit; done
	$(RM) -- $(libc_OBJS) $(start.o_OBJS)
	$(RM) -- $(TARGETS)

install: $(TARGETS)
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) install) || exit; done
	$(MKDIR) $(DESTDIR)$(LIBDIR)
	$(INSTALL) -m 0644 $(OBJDIR)libc.a $(DESTDIR)$(LIBDIR)/libc.a
	$(INSTALL) -m 0755 $(OBJDIR)libc.so.0.0 $(DESTDIR)$(LIBDIR)/libc.so.0.0
	$(LN) -s -- libc.so.0.0 $(DESTDIR)$(LIBDIR)/libc.so.0
	$(LN) -s -- libc.so.0.0 $(DESTDIR)$(LIBDIR)/libc.so
	$(MKDIR) $(DESTDIR)$(LIBDIR)
	$(INSTALL) -m 0644 $(OBJDIR)start.o $(DESTDIR)$(LIBDIR)/start.o

uninstall:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) uninstall) || exit; done
	$(RM) -- $(DESTDIR)$(LIBDIR)/libc.a
	$(RM) -- $(DESTDIR)$(LIBDIR)/libc.so.0.0
	$(RM) -- $(DESTDIR)$(LIBDIR)/libc.so.0
	$(RM) -- $(DESTDIR)$(LIBDIR)/libc.so
	$(RM) -- $(DESTDIR)$(LIBDIR)/start.o

.PHONY: all subdirs clean distclean install uninstall
