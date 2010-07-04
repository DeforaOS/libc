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
	$(INSTALL) -m 0644 -- ioctl.h $(DESTDIR)$(INCLUDEDIR)/compat/sys/ioctl.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat/sys
	$(INSTALL) -m 0644 -- mman.h $(DESTDIR)$(INCLUDEDIR)/compat/sys/mman.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat/sys
	$(INSTALL) -m 0644 -- mount.h $(DESTDIR)$(INCLUDEDIR)/compat/sys/mount.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat/sys
	$(INSTALL) -m 0644 -- reboot.h $(DESTDIR)$(INCLUDEDIR)/compat/sys/reboot.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat/sys
	$(INSTALL) -m 0644 -- resource.h $(DESTDIR)$(INCLUDEDIR)/compat/sys/resource.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat/sys
	$(INSTALL) -m 0644 -- select.h $(DESTDIR)$(INCLUDEDIR)/compat/sys/select.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat/sys
	$(INSTALL) -m 0644 -- shm.h $(DESTDIR)$(INCLUDEDIR)/compat/sys/shm.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat/sys
	$(INSTALL) -m 0644 -- stat.h $(DESTDIR)$(INCLUDEDIR)/compat/sys/stat.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat/sys
	$(INSTALL) -m 0644 -- time.h $(DESTDIR)$(INCLUDEDIR)/compat/sys/time.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat/sys
	$(INSTALL) -m 0644 -- times.h $(DESTDIR)$(INCLUDEDIR)/compat/sys/times.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat/sys
	$(INSTALL) -m 0644 -- types.h $(DESTDIR)$(INCLUDEDIR)/compat/sys/types.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat/sys
	$(INSTALL) -m 0644 -- utsname.h $(DESTDIR)$(INCLUDEDIR)/compat/sys/utsname.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat/sys
	$(INSTALL) -m 0644 -- vt.h $(DESTDIR)$(INCLUDEDIR)/compat/sys/vt.h

uninstall:
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/sys/ioctl.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/sys/mman.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/sys/mount.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/sys/reboot.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/sys/resource.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/sys/select.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/sys/shm.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/sys/stat.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/sys/time.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/sys/times.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/sys/types.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/sys/utsname.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/sys/vt.h

.PHONY: all clean distclean install uninstall
