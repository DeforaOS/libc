TARGETS	= libdl.a libdl.so
PREFIX	= /usr/local
DESTDIR	= 
LIBDIR	= $(PREFIX)/lib
CC	= cc
CPPFLAGSF= -nostdinc -isystem ../../include -isystem ../../include/dl
CPPFLAGS=
CFLAGSF	= -W -DPIC -fPIC
CFLAGS	= -Wall -g -ansi -ffreestanding
AR	= ar -rc
RANLIB	= ranlib
LD	= $(CC) -nostdlib -shared
RM	= rm -f
MKDIR	= mkdir -p
INSTALL	= install


all: $(TARGETS)

libdl_OBJS = dlfcn.o
libdl_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
libdl_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

libdl.a: $(libdl_OBJS)
	$(AR) libdl.a $(libdl_OBJS)
	$(RANLIB) libdl.a

libdl.so: $(libdl_OBJS)
	$(LD) -o libdl.so $(libdl_OBJS)

dlfcn.o: dlfcn.c ../../include/dl/dlfcn.h
	$(CC) $(libdl_CFLAGS) -c dlfcn.c

clean:
	$(RM) $(libdl_OBJS)

distclean: clean
	$(RM) $(TARGETS)

install: all
	$(MKDIR) $(DESTDIR)$(LIBDIR)
	$(INSTALL) -m 0644 libdl.a $(DESTDIR)$(LIBDIR)/libdl.a
	$(INSTALL) -m 0755 libdl.so $(DESTDIR)$(LIBDIR)/libdl.so

uninstall:
	$(RM) $(DESTDIR)$(LIBDIR)/libdl.a
	$(RM) $(DESTDIR)$(LIBDIR)/libdl.so

.PHONY: all clean distclean install uninstall
