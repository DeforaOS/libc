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
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/sys
	$(INSTALL) -m 0644 socket.h $(DESTDIR)$(INCLUDEDIR)/sys/socket.h

uninstall:
	$(RM) $(DESTDIR)$(INCLUDEDIR)/sys/socket.h

.PHONY: all clean distclean install uninstall
