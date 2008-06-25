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
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys
	$(INSTALL) -m 0644 socket.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/socket.h

uninstall:
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/socket.h

.PHONY: all clean distclean install uninstall
