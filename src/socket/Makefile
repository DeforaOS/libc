SUBDIRS	= kernel/freebsd kernel/linux kernel/netbsd
TARGETS	= libsocket.a libsocket.so
PREFIX	= /usr/local
DESTDIR	= 
LIBDIR	= $(PREFIX)/lib
AS	= $(CC)
ASFLAGS	= -W -Wall -g -pedantic -ffreestanding -c
CC	= cc
CPPFLAGSF= -nostdinc -isystem ../../include -isystem ../../include/socket -DPIC
CPPFLAGS=
CFLAGSF	= -W -fPIC
CFLAGS	= -Wall -g -pedantic -ffreestanding
AR	= ar -rc
RANLIB	= ranlib
LD	= $(CC) -nostdlib -shared
RM	= rm -f
LN	= ln -f
MKDIR	= mkdir -p
INSTALL	= install


all: subdirs $(TARGETS)

subdirs:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE)) || exit; done

libsocket_OBJS = arpa/inet.o netdb.o sys/socket.o syscalls.o
libsocket_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
libsocket_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)
libsocket_ASFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(ASFLAGS)

libsocket.a: $(libsocket_OBJS)
	$(AR) libsocket.a $(libsocket_OBJS)
	$(RANLIB) libsocket.a

libsocket.so: $(libsocket_OBJS)
	$(LD) -o libsocket.so -Wl,-soname,libsocket.so.0 $(libsocket_OBJS)

arpa/inet.o: arpa/inet.c
	$(CC) $(libsocket_CFLAGS) -o arpa/inet.o -c arpa/inet.c

netdb.o: netdb.c
	$(CC) $(libsocket_CFLAGS) -c netdb.c

sys/socket.o: sys/socket.c kernel/linux/common.h kernel/netbsd/common.h syscalls.h
	$(CC) $(libsocket_CFLAGS) -o sys/socket.o -c sys/socket.c

syscalls.o: syscalls.S kernel/linux/common.h kernel/linux/amd64/syscalls.S kernel/linux/arm/syscalls.S kernel/linux/i386/syscalls.S kernel/netbsd/amd64/syscalls.S kernel/netbsd/i386/syscalls.S kernel/netbsd/common.h kernel/netbsd/sparc/syscalls.S
	$(AS) $(libsocket_ASFLAGS) -o syscalls.o syscalls.S

clean:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) clean) || exit; done
	$(RM) -- $(libsocket_OBJS)

distclean:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) distclean) || exit; done
	$(RM) -- $(libsocket_OBJS)
	$(RM) -- $(TARGETS)

install: all
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) install) || exit; done
	$(MKDIR) $(DESTDIR)$(LIBDIR)
	$(INSTALL) -m 0644 -- libsocket.a $(DESTDIR)$(LIBDIR)/libsocket.a
	$(INSTALL) -m 0755 -- libsocket.so $(DESTDIR)$(LIBDIR)/libsocket.so.0.0
	$(LN) -s -- libsocket.so.0.0 $(DESTDIR)$(LIBDIR)/libsocket.so.0
	$(LN) -s -- libsocket.so.0.0 $(DESTDIR)$(LIBDIR)/libsocket.so

uninstall:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) uninstall) || exit; done
	$(RM) -- $(DESTDIR)$(LIBDIR)/libsocket.a
	$(RM) -- $(DESTDIR)$(LIBDIR)/libsocket.so.0.0
	$(RM) -- $(DESTDIR)$(LIBDIR)/libsocket.so.0
	$(RM) -- $(DESTDIR)$(LIBDIR)/libsocket.so

.PHONY: all subdirs clean distclean install uninstall
