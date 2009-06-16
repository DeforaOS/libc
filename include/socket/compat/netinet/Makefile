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

install: all
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat/netinet
	$(INSTALL) -m 0644 in.h $(DESTDIR)$(INCLUDEDIR)/compat/netinet/in.h

uninstall:
	$(RM) $(DESTDIR)$(INCLUDEDIR)/compat/netinet/in.h

.PHONY: all clean distclean install uninstall
