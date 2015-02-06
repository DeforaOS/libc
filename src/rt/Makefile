SUBDIRS	= kernel/netbsd
TARGETS	= $(OBJDIR)librt.a $(OBJDIR)librt.so.0.0 $(OBJDIR)librt.so.0 $(OBJDIR)librt.so
OBJDIR	=
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
LDFLAGS	= -nostdlib -lc -L..
AR	= ar
RANLIB	= ranlib
CCSHARED= $(CC) -shared
RM	= rm -f
LN	= ln -f
MKDIR	= mkdir -m 0755 -p
INSTALL	= install


all: subdirs $(TARGETS)

subdirs:
	@for i in $(SUBDIRS); do (cd "$$i" && \
		if [ -n "$(OBJDIR)" ]; then \
		([ -d "$(OBJDIR)$$i" ] || $(MKDIR) -- "$(OBJDIR)$$i") && \
		$(MAKE) OBJDIR="$(OBJDIR)$$i/"; \
		else $(MAKE); fi) || exit; done

librt_OBJS = $(OBJDIR)sched.o $(OBJDIR)syscalls.o
librt_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
librt_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)
librt_ASFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(ASFLAGS)

$(OBJDIR)librt.a: $(librt_OBJS)
	$(AR) -rc $(OBJDIR)librt.a $(librt_OBJS)
	$(RANLIB) $(OBJDIR)librt.a

$(OBJDIR)librt.so.0.0 $(OBJDIR)librt.so.0 $(OBJDIR)librt.so: $(librt_OBJS)
	$(CCSHARED) -o $(OBJDIR)librt.so.0.0 -Wl,-soname,librt.so.0 $(librt_OBJS) $(librt_LDFLAGS)
	$(LN) -s -- librt.so.0.0 $(OBJDIR)librt.so.0
	$(LN) -s -- librt.so.0.0 $(OBJDIR)librt.so

$(OBJDIR)sched.o: sched.c syscalls.h
	$(CC) $(librt_CFLAGS) -o $(OBJDIR)sched.o -c sched.c

$(OBJDIR)syscalls.o: syscalls.S syscalls.h
	$(AS) $(librt_ASFLAGS) -o $(OBJDIR)syscalls.o syscalls.S

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
	$(INSTALL) -m 0644 $(OBJDIR)librt.a $(DESTDIR)$(LIBDIR)/librt.a
	$(INSTALL) -m 0755 $(OBJDIR)librt.so.0.0 $(DESTDIR)$(LIBDIR)/librt.so.0.0
	$(LN) -s -- librt.so.0.0 $(DESTDIR)$(LIBDIR)/librt.so.0
	$(LN) -s -- librt.so.0.0 $(DESTDIR)$(LIBDIR)/librt.so

uninstall:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) uninstall) || exit; done
	$(RM) -- $(DESTDIR)$(LIBDIR)/librt.a
	$(RM) -- $(DESTDIR)$(LIBDIR)/librt.so.0.0
	$(RM) -- $(DESTDIR)$(LIBDIR)/librt.so.0
	$(RM) -- $(DESTDIR)$(LIBDIR)/librt.so

.PHONY: all subdirs clean distclean install uninstall
