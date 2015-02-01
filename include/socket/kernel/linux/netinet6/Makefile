OBJDIR	=
PREFIX	= /usr/local
DESTDIR	=
RM	= rm -f
LN	= ln -f
MKDIR	= mkdir -m 0755 -p
INSTALL	= install
INCLUDEDIR= $(PREFIX)/include


all:

clean:

distclean: clean

install:
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 in6.h $(DESTDIR)$(INCLUDEDIR)/in6.h

uninstall:
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/in6.h

.PHONY: all clean distclean install uninstall
