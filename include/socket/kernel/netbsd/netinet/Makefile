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
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/netinet
	$(INSTALL) -m 0644 -- in.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/netinet/in.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/netinet
	$(INSTALL) -m 0644 -- tcp.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/netinet/tcp.h

uninstall:
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/netinet/in.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/netinet/tcp.h

.PHONY: all clean distclean install uninstall
