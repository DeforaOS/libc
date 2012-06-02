TARGETS	= tracer.so
PREFIX	= /usr/local
DESTDIR	=
LIBDIR	= $(PREFIX)/lib
AS	= $(CC)
ASFLAGS	= -W -fPIC -Wall -g -pedantic -ffreestanding -c
CC	?= cc
CPPFLAGSF= -isystem ../include -DPIC
CPPFLAGS?=
CFLAGSF	= -W -fPIC
CFLAGS	= -Wall -g -O2 -pedantic -ffreestanding
AR	?= ar
RANLIB	?= ranlib
CCSHARED?= $(CC) -shared
RM	?= rm -f
LN	?= ln -f
MKDIR	?= mkdir -p
INSTALL	?= install


all: $(TARGETS)

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
	$(RM) -- $(tracer_OBJS)

distclean: clean
	$(RM) -- $(TARGETS)

install: $(TARGETS)

uninstall:

.PHONY: all clean distclean install uninstall
