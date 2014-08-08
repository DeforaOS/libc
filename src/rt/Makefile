SUBDIRS	= kernel/netbsd
TARGETS	= librt.a librt.so.0.0 librt.so.0 librt.so
PREFIX	= /usr/local
DESTDIR	=
LIBDIR	= $(PREFIX)/lib
AS	= $(CC)
ASFLAGS	= -W -Wall -g -pedantic -ffreestanding -c
CC	= cc
CPPFLAGSF= -nostdinc -isystem ../../include -isystem ../../include/rt -DPIC
CPPFLAGS=
CFLAGSF	= -W -fPIC
CFLAGS	= -Wall -g -O2 -pedantic -ffreestanding
AR	= ar
RANLIB	= ranlib
CCSHARED= $(CC) -nostdlib -shared
RM	= rm -f
LN	= ln -f
MKDIR	= mkdir -m 0755 -p
INSTALL	= install


all: subdirs $(TARGETS)

subdirs:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE)) || exit; done

librt_OBJS = sched.o syscalls.o
librt_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
librt_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)
librt_ASFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(ASFLAGS)

librt.a: $(librt_OBJS)
	$(AR) -rc librt.a $(librt_OBJS)
	$(RANLIB) librt.a

librt.so.0.0 librt.so.0 librt.so: $(librt_OBJS)
	$(CCSHARED) -o librt.so.0.0 -Wl,-soname,librt.so.0 $(librt_OBJS) $(librt_LDFLAGS)
	$(LN) -s -- librt.so.0.0 librt.so.0
	$(LN) -s -- librt.so.0.0 librt.so

sched.o: sched.c syscalls.h
	$(CC) $(librt_CFLAGS) -c sched.c

syscalls.o: syscalls.S syscalls.h
	$(AS) $(librt_ASFLAGS) -o syscalls.o syscalls.S

clean:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) clean) || exit; done
	$(RM) -- $(librt_OBJS)

distclean:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) distclean) || exit; done
	$(RM) -- $(librt_OBJS)
	$(RM) -- $(TARGETS)

install: $(TARGETS)
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) install) || exit; done
	$(MKDIR) $(DESTDIR)$(LIBDIR)
	$(INSTALL) -m 0644 librt.a $(DESTDIR)$(LIBDIR)/librt.a
	$(INSTALL) -m 0755 librt.so.0.0 $(DESTDIR)$(LIBDIR)/librt.so.0.0
	$(LN) -s -- librt.so.0.0 $(DESTDIR)$(LIBDIR)/librt.so.0
	$(LN) -s -- librt.so.0.0 $(DESTDIR)$(LIBDIR)/librt.so

uninstall:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) uninstall) || exit; done
	$(RM) -- $(DESTDIR)$(LIBDIR)/librt.a
	$(RM) -- $(DESTDIR)$(LIBDIR)/librt.so.0.0
	$(RM) -- $(DESTDIR)$(LIBDIR)/librt.so.0
	$(RM) -- $(DESTDIR)$(LIBDIR)/librt.so

.PHONY: all subdirs clean distclean install uninstall
