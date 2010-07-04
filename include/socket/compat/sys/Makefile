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
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat/sys
	$(INSTALL) -m 0644 -- socket.h $(DESTDIR)$(INCLUDEDIR)/compat/sys/socket.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat/sys
	$(INSTALL) -m 0644 -- un.h $(DESTDIR)$(INCLUDEDIR)/compat/sys/un.h

uninstall:
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/sys/socket.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/sys/un.h

.PHONY: all clean distclean install uninstall
