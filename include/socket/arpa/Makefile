PREFIX	= /usr/local
DESTDIR	=
RM	?= rm -f
LN	?= ln -f
MKDIR	?= mkdir -p
INSTALL	?= install
INCLUDEDIR= $(PREFIX)/include


all:

clean:

distclean: clean

install:
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/arpa
	$(INSTALL) -m 0644 -- inet.h $(DESTDIR)$(INCLUDEDIR)/arpa/inet.h

uninstall:
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/arpa/inet.h

.PHONY: all clean distclean install uninstall
