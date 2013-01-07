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
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/netinet
	$(INSTALL) -m 0644 -- in.h $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/netinet/in.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/netinet
	$(INSTALL) -m 0644 -- tcp.h $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/netinet/tcp.h

uninstall:
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/netinet/in.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/netinet/tcp.h

.PHONY: all clean distclean install uninstall
