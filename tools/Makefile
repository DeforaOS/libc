TARGETS	= deforaos-gcc deforaos-gcc.specs tracer.so
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

deforaos-gcc: deforaos-gcc.in subst.sh ../config.sh
	./subst.sh -P "$(PREFIX)" -- "deforaos-gcc"

deforaos-gcc.specs: deforaos-gcc.specs.in subst.sh ../config.sh
	./subst.sh -P "$(PREFIX)" -- "deforaos-gcc.specs"

tracer_OBJS = tracer-analyze.o tracer-syscalls.o
tracer_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
tracer_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)
tracer_ASFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(ASFLAGS)

tracer.so: $(tracer_OBJS)
	$(CCSHARED) -o tracer.so $(tracer_OBJS) $(tracer_LDFLAGS)

tracer-analyze.o: tracer-analyze.c tracer-syscalls.h ../src/syscalls.h tracer-analyze.h
	$(CC) $(tracer_CFLAGS) -c tracer-analyze.c

tracer-syscalls.o: tracer-syscalls.S tracer-analyze.h
	$(AS) $(tracer_ASFLAGS) -o tracer-syscalls.o tracer-syscalls.S

clean:
	$(RM) -- $(deforaos-gcc_OBJS) $(deforaos-gcc.specs_OBJS) $(tracer_OBJS)
	./subst.sh -c -P "$(PREFIX)" -- "deforaos-gcc"
	./subst.sh -c -P "$(PREFIX)" -- "deforaos-gcc.specs"

distclean: clean
	$(RM) -- $(TARGETS)

install: $(TARGETS)
	./subst.sh -P "$(DESTDIR)$(PREFIX)/bin" -i -- "deforaos-gcc"
	./subst.sh -P "$(DESTDIR)$(PREFIX)/lib/gcc" -i -- "deforaos-gcc.specs"

uninstall:
	./subst.sh -P "$(DESTDIR)$(PREFIX)/bin" -u -- "deforaos-gcc"
	./subst.sh -P "$(DESTDIR)$(PREFIX)/lib/gcc" -u -- "deforaos-gcc.specs"

.PHONY: all clean distclean install uninstall
