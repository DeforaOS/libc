SUBDIRS	= kernel/freebsd kernel/linux kernel/netbsd
TARGETS	= $(OBJDIR)libsocket.a $(OBJDIR)libsocket.so.0.0 $(OBJDIR)libsocket.so.0 $(OBJDIR)libsocket.so
OBJDIR	=
PREFIX	= /usr/local
DESTDIR	=
LIBDIR	= $(PREFIX)/lib
AS	= $(CC)
ASFLAGS	= -W -Wall -g -pedantic -ffreestanding -c
CC	= cc
CPPFLAGSF= -nostdinc -isystem ../../include -isystem ../../include/socket -DPIC
CPPFLAGS=
CFLAGSF	= -W -fPIC
CFLAGS	= -Wall -g -O2 -pedantic -ffreestanding
LDFLAGSF= -nostdlib -lc -L..
AR	= ar
RANLIB	= ranlib
CCSHARED= $(CC) -shared
RM	= rm -f
LN	= ln -f
MKDIR	= mkdir -m 0755 -p
INSTALL	= install


all: subdirs $(TARGETS)

subdirs:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE)) || exit; done

libsocket_OBJS = $(OBJDIR)arpa/inet.o $(OBJDIR)netdb.o $(OBJDIR)sys/socket.o $(OBJDIR)syscalls.o
libsocket_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
libsocket_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)
libsocket_ASFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(ASFLAGS)

$(OBJDIR)libsocket.a: $(libsocket_OBJS)
	$(AR) -rc $(OBJDIR)libsocket.a $(libsocket_OBJS)
	$(RANLIB) $(OBJDIR)libsocket.a

$(OBJDIR)libsocket.so.0.0 $(OBJDIR)libsocket.so.0 $(OBJDIR)libsocket.so: $(libsocket_OBJS)
	$(CCSHARED) -o $(OBJDIR)libsocket.so.0.0 -Wl,-soname,libsocket.so.0 $(libsocket_OBJS) $(libsocket_LDFLAGS)
	$(LN) -s -- libsocket.so.0.0 $(OBJDIR)libsocket.so.0
	$(LN) -s -- libsocket.so.0.0 $(OBJDIR)libsocket.so

$(OBJDIR)arpa/inet.o: arpa/inet.c
	$(CC) $(libsocket_CFLAGS) -o $(OBJDIR)arpa/inet.o -c arpa/inet.c

$(OBJDIR)netdb.o: netdb.c
	$(CC) $(libsocket_CFLAGS) -o $(OBJDIR)netdb.o -c netdb.c

$(OBJDIR)sys/socket.o: sys/socket.c kernel/linux/common.h kernel/netbsd/common.h syscalls.h
	$(CC) $(libsocket_CFLAGS) -o $(OBJDIR)sys/socket.o -c sys/socket.c

$(OBJDIR)syscalls.o: syscalls.S kernel/freebsd/common.h kernel/freebsd/amd64/syscalls.S kernel/freebsd/i386/syscalls.S kernel/linux/common.h kernel/linux/amd64/syscalls.S kernel/linux/arm/syscalls.S kernel/linux/i386/syscalls.S kernel/netbsd/amd64/syscalls.S kernel/netbsd/arm/syscalls.S kernel/netbsd/i386/syscalls.S kernel/netbsd/common.h kernel/netbsd/sparc/syscalls.S
	$(AS) $(libsocket_ASFLAGS) -o $(OBJDIR)syscalls.o syscalls.S

clean:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) clean) || exit; done
	$(RM) -- $(libsocket_OBJS)

distclean:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) distclean) || exit; done
	$(RM) -- $(libsocket_OBJS)
	$(RM) -- $(TARGETS)

install: $(TARGETS)
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) install) || exit; done
	$(MKDIR) $(DESTDIR)$(LIBDIR)
	$(INSTALL) -m 0644 $(OBJDIR)libsocket.a $(DESTDIR)$(LIBDIR)/libsocket.a
	$(INSTALL) -m 0755 $(OBJDIR)libsocket.so.0.0 $(DESTDIR)$(LIBDIR)/libsocket.so.0.0
	$(LN) -s -- libsocket.so.0.0 $(DESTDIR)$(LIBDIR)/libsocket.so.0
	$(LN) -s -- libsocket.so.0.0 $(DESTDIR)$(LIBDIR)/libsocket.so

uninstall:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) uninstall) || exit; done
	$(RM) -- $(DESTDIR)$(LIBDIR)/libsocket.a
	$(RM) -- $(DESTDIR)$(LIBDIR)/libsocket.so.0.0
	$(RM) -- $(DESTDIR)$(LIBDIR)/libsocket.so.0
	$(RM) -- $(DESTDIR)$(LIBDIR)/libsocket.so

.PHONY: all subdirs clean distclean install uninstall
