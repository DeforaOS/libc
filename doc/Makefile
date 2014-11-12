SUBDIRS	= gtkdoc
TARGETS	= $(OBJDIR)gtkdoc/libc.types $(OBJDIR)gtkdoc/tmpl.stamp $(OBJDIR)gtkdoc/sgml.stamp $(OBJDIR)gtkdoc/html.stamp
OBJDIR	=
PREFIX	= /usr/local
DESTDIR	=
RM	= rm -f
LN	= ln -f
MKDIR	= mkdir -m 0755 -p
INSTALL	= install


all: subdirs $(TARGETS)

subdirs:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE)) || exit; done

$(OBJDIR)gtkdoc/libc.types:
	./gtkdoc.sh -P "$(PREFIX)" -- "$(OBJDIR)gtkdoc/libc.types"

$(OBJDIR)gtkdoc/tmpl.stamp: $(OBJDIR)gtkdoc/libc.types
	./gtkdoc.sh -P "$(PREFIX)" -- "$(OBJDIR)gtkdoc/tmpl.stamp"

$(OBJDIR)gtkdoc/sgml.stamp: $(OBJDIR)gtkdoc/tmpl.stamp
	./gtkdoc.sh -P "$(PREFIX)" -- "$(OBJDIR)gtkdoc/sgml.stamp"

$(OBJDIR)gtkdoc/html.stamp: gtkdoc/libc-docs.xml $(OBJDIR)gtkdoc/sgml.stamp $(OBJDIR)gtkdoc/tmpl.stamp
	./gtkdoc.sh -P "$(PREFIX)" -- "$(OBJDIR)gtkdoc/html.stamp"

clean:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) clean) || exit; done
	$(RM) -- $(gtkdoc/libc.types_OBJS) $(gtkdoc/tmpl.stamp_OBJS) $(gtkdoc/sgml.stamp_OBJS) $(gtkdoc/html.stamp_OBJS)
	./gtkdoc.sh -c -P "$(PREFIX)" -- "gtkdoc/libc.types"
	./gtkdoc.sh -c -P "$(PREFIX)" -- "gtkdoc/tmpl.stamp"
	./gtkdoc.sh -c -P "$(PREFIX)" -- "gtkdoc/sgml.stamp"
	./gtkdoc.sh -c -P "$(PREFIX)" -- "gtkdoc/html.stamp"

distclean:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) distclean) || exit; done
	$(RM) -- $(gtkdoc/libc.types_OBJS) $(gtkdoc/tmpl.stamp_OBJS) $(gtkdoc/sgml.stamp_OBJS) $(gtkdoc/html.stamp_OBJS)
	./gtkdoc.sh -c -P "$(PREFIX)" -- "gtkdoc/libc.types"
	./gtkdoc.sh -c -P "$(PREFIX)" -- "gtkdoc/tmpl.stamp"
	./gtkdoc.sh -c -P "$(PREFIX)" -- "gtkdoc/sgml.stamp"
	./gtkdoc.sh -c -P "$(PREFIX)" -- "gtkdoc/html.stamp"
	$(RM) -- $(TARGETS)

install: $(TARGETS)
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) install) || exit; done
	./gtkdoc.sh -P "$(DESTDIR)$(PREFIX)" -i -- "$(OBJDIR)gtkdoc/html.stamp"

uninstall:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) uninstall) || exit; done
	./gtkdoc.sh -P "$(DESTDIR)$(PREFIX)" -u -- "gtkdoc/html.stamp"

.PHONY: all subdirs clean distclean install uninstall
