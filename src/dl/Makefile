TARGETS	= $(OBJDIR)libdl.a $(OBJDIR)libdl.so.0.0 libdl.so.0 libdl.so
OBJDIR	=
PREFIX	= /usr/local
DESTDIR	=
LIBDIR	= $(PREFIX)/lib
CC	= cc
CPPFLAGSF= -nostdinc -isystem ../../include -isystem ../../include/dl -DPIC
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


all: $(TARGETS)

libdl_OBJS = $(OBJDIR)dlfcn.o
libdl_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
libdl_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

$(OBJDIR)libdl.a: $(libdl_OBJS)
	$(AR) -rc $(OBJDIR)libdl.a $(libdl_OBJS)
	$(RANLIB) $(OBJDIR)libdl.a

$(OBJDIR)libdl.so.0.0 libdl.so.0 libdl.so: $(libdl_OBJS)
	$(CCSHARED) -o $(OBJDIR)libdl.so.0.0 -Wl,-soname,libdl.so.0 $(libdl_OBJS) $(libdl_LDFLAGS)
	$(LN) -s -- libdl.so.0.0 $(OBJDIR)libdl.so.0
	$(LN) -s -- libdl.so.0.0 $(OBJDIR)libdl.so

$(OBJDIR)dlfcn.o: dlfcn.c ../../include/dl/dlfcn.h ../../include/dl/elf.h
	$(CC) $(libdl_CFLAGS) -o $(OBJDIR)dlfcn.o -c dlfcn.c

clean:
	$(RM) -- $(libdl_OBJS)

distclean: clean
	$(RM) -- $(TARGETS)

install: $(TARGETS)
	$(MKDIR) $(DESTDIR)$(LIBDIR)
	$(INSTALL) -m 0644 $(OBJDIR)libdl.a $(DESTDIR)$(LIBDIR)/libdl.a
	$(INSTALL) -m 0755 $(OBJDIR)libdl.so.0.0 $(DESTDIR)$(LIBDIR)/libdl.so.0.0
	$(LN) -s -- libdl.so.0.0 $(DESTDIR)$(LIBDIR)/libdl.so.0
	$(LN) -s -- libdl.so.0.0 $(DESTDIR)$(LIBDIR)/libdl.so

uninstall:
	$(RM) -- $(DESTDIR)$(LIBDIR)/libdl.a
	$(RM) -- $(DESTDIR)$(LIBDIR)/libdl.so.0.0
	$(RM) -- $(DESTDIR)$(LIBDIR)/libdl.so.0
	$(RM) -- $(DESTDIR)$(LIBDIR)/libdl.so

.PHONY: all clean distclean install uninstall
