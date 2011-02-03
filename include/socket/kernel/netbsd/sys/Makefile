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
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys
	$(INSTALL) -m 0644 -- socket.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/socket.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys
	$(INSTALL) -m 0644 -- un.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/un.h

uninstall:
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/socket.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/un.h

.PHONY: all clean distclean install uninstall
