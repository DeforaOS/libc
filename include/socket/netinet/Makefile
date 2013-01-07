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
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/netinet
	$(INSTALL) -m 0644 -- in.h $(DESTDIR)$(INCLUDEDIR)/netinet/in.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/netinet
	$(INSTALL) -m 0644 -- tcp.h $(DESTDIR)$(INCLUDEDIR)/netinet/tcp.h

uninstall:
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/netinet/in.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/netinet/tcp.h

.PHONY: all clean distclean install uninstall
