PREFIX	= /usr/local
DESTDIR	=
RM	= rm -f
LN	= ln -f
MKDIR	= mkdir -p
INSTALL	= install
INCLUDEDIR= $(PREFIX)/include


all:

clean:

distclean: clean

install:
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- math.h $(DESTDIR)$(INCLUDEDIR)/math.h

uninstall:
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/math.h

.PHONY: all clean distclean install uninstall
