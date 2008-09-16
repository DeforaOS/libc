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
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys
	$(INSTALL) -m 0644 ioctl.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/ioctl.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys
	$(INSTALL) -m 0644 mman.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/mman.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys
	$(INSTALL) -m 0644 mount.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/mount.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys
	$(INSTALL) -m 0644 reboot.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/reboot.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys
	$(INSTALL) -m 0644 resource.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/resource.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys
	$(INSTALL) -m 0644 select.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/select.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys
	$(INSTALL) -m 0644 stat.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/stat.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys
	$(INSTALL) -m 0644 time.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/time.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys
	$(INSTALL) -m 0644 times.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/times.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys
	$(INSTALL) -m 0644 types.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/types.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys
	$(INSTALL) -m 0644 utsname.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/utsname.h

uninstall:
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/ioctl.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/mman.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/mount.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/reboot.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/resource.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/select.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/stat.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/time.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/times.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/types.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/utsname.h

.PHONY: all clean distclean install uninstall
