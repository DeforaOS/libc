TARGETS	= libm.a libm.so
PREFIX	= /usr/local
DESTDIR	= 
LIBDIR	= $(PREFIX)/lib
CC	= cc
CPPFLAGSF= -nostdinc -I ../../include -I ../../include/math
CPPFLAGS=
CFLAGSF	= -W
CFLAGS	= -Wall -g -ansi -ffreestanding
AS	= $(CC)
ASFLAGS	= $(CFLAGS) -c
AR	= ar -rc
RANLIB	= ranlib
LD	= $(CC) -shared
RM	= rm -f
MKDIR	= mkdir -p
INSTALL	= install


all: $(TARGETS)

libm_OBJS = arch.o math.o
libm_ASFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(ASFLAGS)
libm_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
libm_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

libm.a: $(libm_OBJS)
	$(AR) libm.a $(libm_OBJS)
	$(RANLIB) libm.a

libm.so: $(libm_OBJS)
	$(LD) -o libm.so $(libm_OBJS)

arch.o: arch.S amd64/math.S i386/math.S
	$(AS) $(libm_ASFLAGS) -o arch.o arch.S

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
