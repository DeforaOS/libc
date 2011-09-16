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
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat/net
	$(INSTALL) -m 0644 -- if.h $(DESTDIR)$(INCLUDEDIR)/compat/net/if.h

uninstall:
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/net/if.h

.PHONY: all clean distclean install uninstall
