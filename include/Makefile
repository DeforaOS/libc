SUBDIRS	= compat dl kernel/freebsd kernel/linux kernel/netbsd kernel/openbsd kernel/solaris math net pthread socket sys
PREFIX	= /usr/local
DESTDIR	=
RM	= rm -f
LN	= ln -f
MKDIR	= mkdir -p
INSTALL	= install
INCLUDEDIR= $(PREFIX)/include


all: subdirs

subdirs:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE)) || exit; done

clean:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) clean) || exit; done

distclean:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) distclean) || exit; done

install:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) install) || exit; done
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- assert.h $(DESTDIR)$(INCLUDEDIR)/assert.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- complex.h $(DESTDIR)$(INCLUDEDIR)/complex.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- ctype.h $(DESTDIR)$(INCLUDEDIR)/ctype.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- dirent.h $(DESTDIR)$(INCLUDEDIR)/dirent.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- errno.h $(DESTDIR)$(INCLUDEDIR)/errno.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- fcntl.h $(DESTDIR)$(INCLUDEDIR)/fcntl.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- float.h $(DESTDIR)$(INCLUDEDIR)/float.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- fnmatch.h $(DESTDIR)$(INCLUDEDIR)/fnmatch.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- glob.h $(DESTDIR)$(INCLUDEDIR)/glob.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- grp.h $(DESTDIR)$(INCLUDEDIR)/grp.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- iconv.h $(DESTDIR)$(INCLUDEDIR)/iconv.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- inttypes.h $(DESTDIR)$(INCLUDEDIR)/inttypes.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- langinfo.h $(DESTDIR)$(INCLUDEDIR)/langinfo.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- libgen.h $(DESTDIR)$(INCLUDEDIR)/libgen.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- limits.h $(DESTDIR)$(INCLUDEDIR)/limits.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- locale.h $(DESTDIR)$(INCLUDEDIR)/locale.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- nl_types.h $(DESTDIR)$(INCLUDEDIR)/nl_types.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- poll.h $(DESTDIR)$(INCLUDEDIR)/poll.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- pwd.h $(DESTDIR)$(INCLUDEDIR)/pwd.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- sched.h $(DESTDIR)$(INCLUDEDIR)/sched.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- search.h $(DESTDIR)$(INCLUDEDIR)/search.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- setjmp.h $(DESTDIR)$(INCLUDEDIR)/setjmp.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- signal.h $(DESTDIR)$(INCLUDEDIR)/signal.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- stdarg.h $(DESTDIR)$(INCLUDEDIR)/stdarg.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- stdbool.h $(DESTDIR)$(INCLUDEDIR)/stdbool.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- stddef.h $(DESTDIR)$(INCLUDEDIR)/stddef.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- stdint.h $(DESTDIR)$(INCLUDEDIR)/stdint.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- stdio.h $(DESTDIR)$(INCLUDEDIR)/stdio.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- stdlib.h $(DESTDIR)$(INCLUDEDIR)/stdlib.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- string.h $(DESTDIR)$(INCLUDEDIR)/string.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- strings.h $(DESTDIR)$(INCLUDEDIR)/strings.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- stropts.h $(DESTDIR)$(INCLUDEDIR)/stropts.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- syslog.h $(DESTDIR)$(INCLUDEDIR)/syslog.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- termios.h $(DESTDIR)$(INCLUDEDIR)/termios.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- time.h $(DESTDIR)$(INCLUDEDIR)/time.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- ucontext.h $(DESTDIR)$(INCLUDEDIR)/ucontext.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- unistd.h $(DESTDIR)$(INCLUDEDIR)/unistd.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- utime.h $(DESTDIR)$(INCLUDEDIR)/utime.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- utmpx.h $(DESTDIR)$(INCLUDEDIR)/utmpx.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- wchar.h $(DESTDIR)$(INCLUDEDIR)/wchar.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- wctype.h $(DESTDIR)$(INCLUDEDIR)/wctype.h

uninstall:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) uninstall) || exit; done
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/assert.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/complex.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/ctype.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/dirent.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/errno.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/fcntl.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/float.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/fnmatch.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/glob.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/grp.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/iconv.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/inttypes.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/langinfo.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/libgen.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/limits.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/locale.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/nl_types.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/poll.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/pwd.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/sched.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/search.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/setjmp.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/signal.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/stdarg.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/stdbool.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/stddef.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/stdint.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/stdio.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/stdlib.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/string.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/strings.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/stropts.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/syslog.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/termios.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/time.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/ucontext.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/unistd.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/utime.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/utmpx.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/wchar.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/wctype.h

.PHONY: all subdirs clean distclean install uninstall
