TARGETS	= librt.a librt.so.0.0 librt.so.0 librt.so
PREFIX	= /usr/local
DESTDIR	=
LIBDIR	= $(PREFIX)/lib
CC	?= cc
CPPFLAGSF= -nostdinc -isystem ../../include -isystem ../../include/rt -DPIC
CPPFLAGS?=
CFLAGSF	= -W -fPIC
CFLAGS	= -Wall -g -O2 -pedantic -ffreestanding
AR	?= ar
RANLIB	?= ranlib
CCSHARED= $(CC) -nostdlib -shared
RM	?= rm -f
LN	?= ln -f
MKDIR	?= mkdir -p
INSTALL	?= install


all: $(TARGETS)

librt_OBJS = sched.o
librt_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
librt_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

librt.a: $(librt_OBJS)
	$(AR) -rc librt.a $(librt_OBJS)
	$(RANLIB) librt.a

librt.so.0.0 librt.so.0 librt.so: $(librt_OBJS)
	$(CCSHARED) -o librt.so.0.0 -Wl,-soname,librt.so.0 $(librt_OBJS) $(librt_LDFLAGS)
	$(LN) -s -- librt.so.0.0 librt.so.0
	$(LN) -s -- librt.so.0.0 librt.so

sched.o: sched.c
	$(CC) $(librt_CFLAGS) -c sched.c

clean:
	$(RM) -- $(librt_OBJS)

distclean: clean
	$(RM) -- $(TARGETS)

install: $(TARGETS)
	$(MKDIR) $(DESTDIR)$(LIBDIR)
	$(INSTALL) -m 0644 -- librt.a $(DESTDIR)$(LIBDIR)/librt.a
	$(INSTALL) -m 0755 -- librt.so.0.0 $(DESTDIR)$(LIBDIR)/librt.so.0.0
	$(LN) -s -- librt.so.0.0 $(DESTDIR)$(LIBDIR)/librt.so.0
	$(LN) -s -- librt.so.0.0 $(DESTDIR)$(LIBDIR)/librt.so

uninstall:
	$(RM) -- $(DESTDIR)$(LIBDIR)/librt.a
	$(RM) -- $(DESTDIR)$(LIBDIR)/librt.so.0.0
	$(RM) -- $(DESTDIR)$(LIBDIR)/librt.so.0
	$(RM) -- $(DESTDIR)$(LIBDIR)/librt.so

.PHONY: all clean distclean install uninstall
