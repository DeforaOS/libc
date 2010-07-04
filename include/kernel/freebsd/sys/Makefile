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
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys
	$(INSTALL) -m 0644 -- mman.h $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys/mman.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys
	$(INSTALL) -m 0644 -- resource.h $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys/resource.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys
	$(INSTALL) -m 0644 -- select.h $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys/select.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys
	$(INSTALL) -m 0644 -- shm.h $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys/shm.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys
	$(INSTALL) -m 0644 -- stat.h $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys/stat.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys
	$(INSTALL) -m 0644 -- time.h $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys/time.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys
	$(INSTALL) -m 0644 -- times.h $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys/times.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys
	$(INSTALL) -m 0644 -- types.h $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys/types.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys
	$(INSTALL) -m 0644 -- utsname.h $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys/utsname.h

uninstall:
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys/mman.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys/resource.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys/select.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys/shm.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys/stat.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys/time.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys/times.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys/types.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys/utsname.h

.PHONY: all clean distclean install uninstall
