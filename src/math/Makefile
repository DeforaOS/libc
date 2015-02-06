SUBDIRS	= amd64 i386
TARGETS	= $(OBJDIR)libm.a $(OBJDIR)libm.so.0.0 $(OBJDIR)libm.so.0 $(OBJDIR)libm.so
OBJDIR	=
PREFIX	= /usr/local
DESTDIR	=
LIBDIR	= $(PREFIX)/lib
AS	= $(CC)
ASFLAGS	= -W -Wall -g -pedantic -ffreestanding -c
CC	= cc
CPPFLAGSF= -nostdinc -isystem ../../include -isystem ../../include/math -DPIC
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
	@for i in $(SUBDIRS); do (cd "$$i" && \
		if [ -n "$(OBJDIR)" ]; then \
		([ -d "$(OBJDIR)$$i" ] || $(MKDIR) -- "$(OBJDIR)$$i") && \
		$(MAKE) OBJDIR="$(OBJDIR)$$i/"; \
		else $(MAKE); fi) || exit; done

libm_OBJS = $(OBJDIR)arch.o $(OBJDIR)math.o
libm_ASFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(ASFLAGS)
libm_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
libm_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

$(OBJDIR)libm.a: $(libm_OBJS)
	$(AR) -rc $(OBJDIR)libm.a $(libm_OBJS)
	$(RANLIB) $(OBJDIR)libm.a

$(OBJDIR)libm.so.0.0 $(OBJDIR)libm.so.0 $(OBJDIR)libm.so: $(libm_OBJS)
	$(CCSHARED) -o $(OBJDIR)libm.so.0.0 -Wl,-soname,libm.so.0 $(libm_OBJS) $(libm_LDFLAGS)
	$(LN) -s -- libm.so.0.0 $(OBJDIR)libm.so.0
	$(LN) -s -- libm.so.0.0 $(OBJDIR)libm.so

$(OBJDIR)arch.o: arch.S amd64/math.S i386/math.S
	$(AS) $(libm_ASFLAGS) -o $(OBJDIR)arch.o arch.S

$(OBJDIR)math.o: math.c ../../include/math/math.h
	$(CC) $(libm_CFLAGS) -o $(OBJDIR)math.o -c math.c

clean:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) clean) || exit; done
	$(RM) -- $(libm_OBJS)

distclean:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) distclean) || exit; done
	$(RM) -- $(libm_OBJS)
	$(RM) -- $(TARGETS)

install: $(TARGETS)
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) install) || exit; done
	$(MKDIR) $(DESTDIR)$(LIBDIR)
	$(INSTALL) -m 0644 $(OBJDIR)libm.a $(DESTDIR)$(LIBDIR)/libm.a
	$(INSTALL) -m 0755 $(OBJDIR)libm.so.0.0 $(DESTDIR)$(LIBDIR)/libm.so.0.0
	$(LN) -s -- libm.so.0.0 $(DESTDIR)$(LIBDIR)/libm.so.0
	$(LN) -s -- libm.so.0.0 $(DESTDIR)$(LIBDIR)/libm.so

uninstall:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) uninstall) || exit; done
	$(RM) -- $(DESTDIR)$(LIBDIR)/libm.a
	$(RM) -- $(DESTDIR)$(LIBDIR)/libm.so.0.0
	$(RM) -- $(DESTDIR)$(LIBDIR)/libm.so.0
	$(RM) -- $(DESTDIR)$(LIBDIR)/libm.so

.PHONY: all subdirs clean distclean install uninstall
