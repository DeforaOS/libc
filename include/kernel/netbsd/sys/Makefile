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
	$(INSTALL) -m 0644 ioctl.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/ioctl.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys
	$(INSTALL) -m 0644 mman.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/mman.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys
	$(INSTALL) -m 0644 mount.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/mount.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys
	$(INSTALL) -m 0644 reboot.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/reboot.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys
	$(INSTALL) -m 0644 resource.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/resource.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys
	$(INSTALL) -m 0644 select.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/select.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys
	$(INSTALL) -m 0644 shm.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/shm.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys
	$(INSTALL) -m 0644 stat.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/stat.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys
	$(INSTALL) -m 0644 time.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/time.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys
	$(INSTALL) -m 0644 times.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/times.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys
	$(INSTALL) -m 0644 types.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/types.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys
	$(INSTALL) -m 0644 utsname.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/utsname.h

uninstall:
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/ioctl.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/mman.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/mount.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/reboot.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/resource.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/select.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/shm.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/stat.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/time.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/times.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/types.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/sys/utsname.h

.PHONY: all clean distclean install uninstall
