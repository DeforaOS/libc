TARGETS	= libm.a libm.so
PREFIX	= /usr/local
DESTDIR	= 
LIBDIR	= $(PREFIX)/lib
CC	= cc
CPPFLAGSF= -nostdinc -I ../../include -I ../../include/math
CPPFLAGS=
CFLAGSF	= -W
CFLAGS	= -Wall -g -ansi -ffreestanding
AR	= ar -rc
RANLIB	= ranlib
LD	= $(CC) -shared
RM	= rm -f
MKDIR	= mkdir -p
INSTALL	= install


all: $(TARGETS)

libm_OBJS = math.o
libm_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS) -fPIC

libm.a: $(libm_OBJS)
	$(AR) libm.a $(libm_OBJS)
	$(RANLIB) libm.a

libm.so: $(libm_OBJS)
	$(LD) -o libm.so $(libm_OBJS)

math.o: math.c ../../include/math/math.h
	$(CC) $(libm_CFLAGS) -c math.c

clean:
	$(RM) $(libm_OBJS)

distclean: clean
	$(RM) $(TARGETS)

install: all
	$(MKDIR) $(DESTDIR)$(LIBDIR)
	$(INSTALL) -m 0644 libm.a $(DESTDIR)$(LIBDIR)/libm.a
	$(INSTALL) -m 0755 libm.so $(DESTDIR)$(LIBDIR)/libm.so

uninstall:
	$(RM) $(DESTDIR)$(LIBDIR)/libm.a
	$(RM) $(DESTDIR)$(LIBDIR)/libm.so

.PHONY: all clean distclean install uninstall
