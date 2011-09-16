TARGETS	= libdl.a libdl.so
PREFIX	= /usr/local
DESTDIR	=
LIBDIR	= $(PREFIX)/lib
CC	= cc
CPPFLAGSF= -nostdinc -isystem ../../include -isystem ../../include/dl -DPIC
CPPFLAGS?=
CFLAGSF	= -W -fPIC
CFLAGS	= -Wall -g -pedantic -ffreestanding
AR	?= ar
RANLIB	?= ranlib
CCSHARED= $(CC) -nostdlib -shared
RM	?= rm -f
LN	?= ln -f
MKDIR	?= mkdir -p
INSTALL	?= install


all: $(TARGETS)

libdl_OBJS = dlfcn.o
libdl_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
libdl_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

libdl.a: $(libdl_OBJS)
	$(AR) -rc libdl.a $(libdl_OBJS)
	$(RANLIB) libdl.a

libdl.so: $(libdl_OBJS)
	$(CCSHARED) -o libdl.so -Wl,-soname,libdl.so.0 $(libdl_OBJS) $(libdl_LDFLAGS)

dlfcn.o: dlfcn.c ../../include/dl/dlfcn.h ../../include/dl/elf.h
	$(CC) $(libdl_CFLAGS) -c dlfcn.c

clean:
	$(RM) -- $(libdl_OBJS)

distclean: clean
	$(RM) -- $(TARGETS)

install: $(TARGETS)
	$(MKDIR) $(DESTDIR)$(LIBDIR)
	$(INSTALL) -m 0644 -- libdl.a $(DESTDIR)$(LIBDIR)/libdl.a
	$(INSTALL) -m 0755 -- libdl.so $(DESTDIR)$(LIBDIR)/libdl.so.0.0
	$(LN) -s -- libdl.so.0.0 $(DESTDIR)$(LIBDIR)/libdl.so.0
	$(LN) -s -- libdl.so.0.0 $(DESTDIR)$(LIBDIR)/libdl.so

uninstall:
	$(RM) -- $(DESTDIR)$(LIBDIR)/libdl.a
	$(RM) -- $(DESTDIR)$(LIBDIR)/libdl.so.0.0
	$(RM) -- $(DESTDIR)$(LIBDIR)/libdl.so.0
	$(RM) -- $(DESTDIR)$(LIBDIR)/libdl.so

.PHONY: all clean distclean install uninstall
