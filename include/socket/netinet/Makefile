PREFIX	= /usr/local
DESTDIR	= 
RM	= rm -f
MKDIR	= mkdir -p
INSTALL	= install
INCLUDEDIR= $(PREFIX)/include


all:

clean:

distclean: clean

install: all
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/netinet
	$(INSTALL) -m 0644 in.h $(DESTDIR)$(INCLUDEDIR)/netinet/in.h

uninstall:
	$(RM) $(DESTDIR)$(INCLUDEDIR)/netinet/in.h

.PHONY: all clean distclean install uninstall
