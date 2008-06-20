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
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 arpa/inet.h $(DESTDIR)$(INCLUDEDIR)/arpa/inet.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 netdb.h $(DESTDIR)$(INCLUDEDIR)/netdb.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 netinet/in.h $(DESTDIR)$(INCLUDEDIR)/netinet/in.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 sys/socket.h $(DESTDIR)$(INCLUDEDIR)/sys/socket.h

uninstall:
	$(RM) $(DESTDIR)$(INCLUDEDIR)/arpa/inet.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/netdb.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/netinet/in.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/sys/socket.h

.PHONY: all clean distclean install uninstall
