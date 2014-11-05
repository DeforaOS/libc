TARGETS	= $(OBJDIR)deforaos-gcc $(OBJDIR)deforaos-gcc.specs $(OBJDIR)tracer.so
OBJDIR	=
PREFIX	= /usr/local
DESTDIR	=
LIBDIR	= $(PREFIX)/lib
AS	= $(CC)
ASFLAGS	= -W -fPIC -Wall -g -pedantic -ffreestanding -c
CC	= cc
CPPFLAGSF= -isystem ../include -DPIC
CPPFLAGS=
CFLAGSF	= -W -fPIC
CFLAGS	= -Wall -g -O2 -pedantic -ffreestanding
AR	= ar
RANLIB	= ranlib
CCSHARED= $(CC) -shared
RM	= rm -f
LN	= ln -f
MKDIR	= mkdir -m 0755 -p
INSTALL	= install


all: $(TARGETS)

$(OBJDIR)deforaos-gcc: deforaos-gcc.in subst.sh ../config.sh
	./subst.sh -P "$(PREFIX)" -- "$(OBJDIR)deforaos-gcc"

$(OBJDIR)deforaos-gcc.specs: deforaos-gcc.specs.in subst.sh ../config.sh
	./subst.sh -P "$(PREFIX)" -- "$(OBJDIR)deforaos-gcc.specs"

tracer_OBJS = $(OBJDIR)tracer-analyze.o $(OBJDIR)tracer-syscalls.o
tracer_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
tracer_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)
tracer_ASFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(ASFLAGS)

$(OBJDIR)tracer.so: $(tracer_OBJS)
	$(CCSHARED) -o $(OBJDIR)tracer.so $(tracer_OBJS) $(tracer_LDFLAGS)

$(OBJDIR)tracer-analyze.o: tracer-analyze.c tracer-syscalls.h ../src/syscalls.h tracer-analyze.h
	$(CC) $(tracer_CFLAGS) -o $(OBJDIR)tracer-analyze.o -c tracer-analyze.c

$(OBJDIR)tracer-syscalls.o: tracer-syscalls.S tracer-analyze.h
	$(AS) $(tracer_ASFLAGS) -o $(OBJDIR)tracer-syscalls.o tracer-syscalls.S

clean:
	$(RM) -- $(deforaos-gcc_OBJS) $(deforaos-gcc.specs_OBJS) $(tracer_OBJS)
	./subst.sh -c -P "$(PREFIX)" -- "deforaos-gcc"
	./subst.sh -c -P "$(PREFIX)" -- "deforaos-gcc.specs"

distclean: clean
	$(RM) -- $(TARGETS)

install: $(TARGETS)
	./subst.sh -P "$(DESTDIR)$(PREFIX)/bin" -i -- "$(OBJDIR)deforaos-gcc"
	./subst.sh -P "$(DESTDIR)$(PREFIX)/lib/gcc" -i -- "$(OBJDIR)deforaos-gcc.specs"

uninstall:
	./subst.sh -P "$(DESTDIR)$(PREFIX)/bin" -u -- "deforaos-gcc"
	./subst.sh -P "$(DESTDIR)$(PREFIX)/lib/gcc" -u -- "deforaos-gcc.specs"

.PHONY: all clean distclean install uninstall
