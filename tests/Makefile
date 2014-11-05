TARGETS	= $(OBJDIR)dlfcn $(OBJDIR)errno $(OBJDIR)fnmatch $(OBJDIR)includes $(OBJDIR)langinfo $(OBJDIR)netdb $(OBJDIR)ptrace $(OBJDIR)pwd $(OBJDIR)regex $(OBJDIR)rt $(OBJDIR)select $(OBJDIR)setjmp $(OBJDIR)signal $(OBJDIR)socket $(OBJDIR)start $(OBJDIR)stdarg $(OBJDIR)stdint $(OBJDIR)stdio $(OBJDIR)stdlib $(OBJDIR)string $(OBJDIR)time $(OBJDIR)tests.log $(OBJDIR)unistd
OBJDIR	=
PREFIX	= /usr/local
DESTDIR	=
BINDIR	= $(PREFIX)/bin
SBINDIR	= $(PREFIX)/sbin
CC	= cc
CPPFLAGSF= -nostdinc -isystem ../include -isystem ../include/pthread -isystem ../include/rt
CPPFLAGS=
CFLAGSF	= -W
CFLAGS	= -Wall -g -O2 -ffreestanding
LDFLAGSF= -nostdlib -L../src -Wl,-rpath,$(PWD)/../src -lc ../src/start.o
LDFLAGS	= `$(CC) -print-libgcc-file-name`
RM	= rm -f
LN	= ln -f
MKDIR	= mkdir -m 0755 -p
INSTALL	= install


all: $(TARGETS)

dlfcn_OBJS = $(OBJDIR)dlfcn.o
dlfcn_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) -isystem ../include/dl $(CFLAGSF) $(CFLAGS)
dlfcn_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

$(OBJDIR)dlfcn: $(dlfcn_OBJS)
	$(CC) -o $(OBJDIR)dlfcn $(dlfcn_OBJS) $(dlfcn_LDFLAGS)

errno_OBJS = $(OBJDIR)errno.o
errno_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
errno_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

$(OBJDIR)errno: $(errno_OBJS)
	$(CC) -o $(OBJDIR)errno $(errno_OBJS) $(errno_LDFLAGS)

fnmatch_OBJS = $(OBJDIR)fnmatch.o
fnmatch_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
fnmatch_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

$(OBJDIR)fnmatch: $(fnmatch_OBJS)
	$(CC) -o $(OBJDIR)fnmatch $(fnmatch_OBJS) $(fnmatch_LDFLAGS)

includes_OBJS = $(OBJDIR)includes.o
includes_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
includes_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

$(OBJDIR)includes: $(includes_OBJS)
	$(CC) -o $(OBJDIR)includes $(includes_OBJS) $(includes_LDFLAGS)

langinfo_OBJS = $(OBJDIR)langinfo.o
langinfo_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
langinfo_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

$(OBJDIR)langinfo: $(langinfo_OBJS)
	$(CC) -o $(OBJDIR)langinfo $(langinfo_OBJS) $(langinfo_LDFLAGS)

netdb_OBJS = $(OBJDIR)netdb.o
netdb_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) -isystem ../include/socket $(CFLAGSF) $(CFLAGS)
netdb_LDFLAGS = $(LDFLAGSF) $(LDFLAGS) ../src/socket/libsocket.a

$(OBJDIR)netdb: $(netdb_OBJS)
	$(CC) -o $(OBJDIR)netdb $(netdb_OBJS) $(netdb_LDFLAGS)

ptrace_OBJS = $(OBJDIR)ptrace.o
ptrace_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
ptrace_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

$(OBJDIR)ptrace: $(ptrace_OBJS)
	$(CC) -o $(OBJDIR)ptrace $(ptrace_OBJS) $(ptrace_LDFLAGS)

pwd_OBJS = $(OBJDIR)pwd.o
pwd_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
pwd_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

$(OBJDIR)pwd: $(pwd_OBJS)
	$(CC) -o $(OBJDIR)pwd $(pwd_OBJS) $(pwd_LDFLAGS)

regex_OBJS = $(OBJDIR)regex.o
regex_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
regex_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

$(OBJDIR)regex: $(regex_OBJS)
	$(CC) -o $(OBJDIR)regex $(regex_OBJS) $(regex_LDFLAGS)

rt_OBJS = $(OBJDIR)rt.o
rt_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
rt_LDFLAGS = $(LDFLAGSF) $(LDFLAGS) ../src/rt/librt.a

$(OBJDIR)rt: $(rt_OBJS)
	$(CC) -o $(OBJDIR)rt $(rt_OBJS) $(rt_LDFLAGS)

select_OBJS = $(OBJDIR)select.o
select_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
select_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

$(OBJDIR)select: $(select_OBJS)
	$(CC) -o $(OBJDIR)select $(select_OBJS) $(select_LDFLAGS)

setjmp_OBJS = $(OBJDIR)setjmp.o
setjmp_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
setjmp_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

$(OBJDIR)setjmp: $(setjmp_OBJS)
	$(CC) -o $(OBJDIR)setjmp $(setjmp_OBJS) $(setjmp_LDFLAGS)

signal_OBJS = $(OBJDIR)signal.o
signal_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
signal_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

$(OBJDIR)signal: $(signal_OBJS)
	$(CC) -o $(OBJDIR)signal $(signal_OBJS) $(signal_LDFLAGS)

socket_OBJS = $(OBJDIR)socket.o
socket_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
socket_LDFLAGS = $(LDFLAGSF) $(LDFLAGS) ../src/socket/libsocket.a

$(OBJDIR)socket: $(socket_OBJS)
	$(CC) -o $(OBJDIR)socket $(socket_OBJS) $(socket_LDFLAGS)

start_OBJS = $(OBJDIR)start.o
start_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
start_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

$(OBJDIR)start: $(start_OBJS)
	$(CC) -o $(OBJDIR)start $(start_OBJS) $(start_LDFLAGS)

stdarg_OBJS = $(OBJDIR)stdarg.o
stdarg_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
stdarg_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

$(OBJDIR)stdarg: $(stdarg_OBJS)
	$(CC) -o $(OBJDIR)stdarg $(stdarg_OBJS) $(stdarg_LDFLAGS)

stdint_OBJS = $(OBJDIR)stdint.o
stdint_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
stdint_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

$(OBJDIR)stdint: $(stdint_OBJS)
	$(CC) -o $(OBJDIR)stdint $(stdint_OBJS) $(stdint_LDFLAGS)

stdio_OBJS = $(OBJDIR)stdio.o
stdio_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
stdio_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

$(OBJDIR)stdio: $(stdio_OBJS)
	$(CC) -o $(OBJDIR)stdio $(stdio_OBJS) $(stdio_LDFLAGS)

stdlib_OBJS = $(OBJDIR)stdlib.o
stdlib_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
stdlib_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

$(OBJDIR)stdlib: $(stdlib_OBJS)
	$(CC) -o $(OBJDIR)stdlib $(stdlib_OBJS) $(stdlib_LDFLAGS)

string_OBJS = $(OBJDIR)string.o
string_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
string_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

$(OBJDIR)string: $(string_OBJS)
	$(CC) -o $(OBJDIR)string $(string_OBJS) $(string_LDFLAGS)

time_OBJS = $(OBJDIR)time.o
time_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
time_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

$(OBJDIR)time: $(time_OBJS)
	$(CC) -o $(OBJDIR)time $(time_OBJS) $(time_LDFLAGS)

$(OBJDIR)tests.log: $(OBJDIR)dlfcn $(OBJDIR)errno $(OBJDIR)fnmatch $(OBJDIR)includes $(OBJDIR)langinfo $(OBJDIR)netdb $(OBJDIR)ptrace $(OBJDIR)pwd $(OBJDIR)regex $(OBJDIR)rt $(OBJDIR)select $(OBJDIR)setjmp $(OBJDIR)signal $(OBJDIR)socket $(OBJDIR)start $(OBJDIR)stdarg $(OBJDIR)stdint $(OBJDIR)stdio $(OBJDIR)stdlib $(OBJDIR)string $(OBJDIR)time tests.sh $(OBJDIR)unistd
	./tests.sh -P "$(PREFIX)" -- "$(OBJDIR)tests.log"

unistd_OBJS = $(OBJDIR)unistd.o
unistd_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
unistd_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

$(OBJDIR)unistd: $(unistd_OBJS)
	$(CC) -o $(OBJDIR)unistd $(unistd_OBJS) $(unistd_LDFLAGS)

$(OBJDIR)dlfcn.o: dlfcn.c ../src/dl/libdl.a ../src/libc.a ../src/start.o
	$(CC) $(dlfcn_CFLAGS) -o $(OBJDIR)dlfcn.o -c dlfcn.c

$(OBJDIR)errno.o: errno.c ../src/libc.a ../src/start.o
	$(CC) $(errno_CFLAGS) -o $(OBJDIR)errno.o -c errno.c

$(OBJDIR)fnmatch.o: fnmatch.c ../src/libc.a ../src/start.o
	$(CC) $(fnmatch_CFLAGS) -o $(OBJDIR)fnmatch.o -c fnmatch.c

$(OBJDIR)includes.o: includes.c ../src/libc.a ../src/start.o
	$(CC) $(includes_CFLAGS) -o $(OBJDIR)includes.o -c includes.c

$(OBJDIR)langinfo.o: langinfo.c ../src/libc.a ../src/start.o
	$(CC) $(langinfo_CFLAGS) -o $(OBJDIR)langinfo.o -c langinfo.c

$(OBJDIR)netdb.o: netdb.c ../src/libc.a ../src/socket/libsocket.a ../src/start.o
	$(CC) $(netdb_CFLAGS) -o $(OBJDIR)netdb.o -c netdb.c

$(OBJDIR)ptrace.o: ptrace.c ../src/libc.a ../src/start.o
	$(CC) $(ptrace_CFLAGS) -o $(OBJDIR)ptrace.o -c ptrace.c

$(OBJDIR)pwd.o: pwd.c ../src/libc.a ../src/start.o
	$(CC) $(pwd_CFLAGS) -o $(OBJDIR)pwd.o -c pwd.c

$(OBJDIR)regex.o: regex.c ../src/libc.a ../src/start.o
	$(CC) $(regex_CFLAGS) -o $(OBJDIR)regex.o -c regex.c

$(OBJDIR)rt.o: rt.c ../src/rt/librt.a ../src/libc.a ../src/start.o
	$(CC) -isystem ../include/rt $(rt_CFLAGS) -o $(OBJDIR)rt.o -c rt.c

$(OBJDIR)select.o: select.c ../src/libc.a ../src/start.o
	$(CC) $(select_CFLAGS) -o $(OBJDIR)select.o -c select.c

$(OBJDIR)setjmp.o: setjmp.c ../src/libc.a ../src/start.o
	$(CC) $(setjmp_CFLAGS) -o $(OBJDIR)setjmp.o -c setjmp.c

$(OBJDIR)signal.o: signal.c ../src/libc.a ../src/start.o
	$(CC) $(signal_CFLAGS) -o $(OBJDIR)signal.o -c signal.c

$(OBJDIR)socket.o: socket.c ../src/socket/libsocket.a ../src/libc.a ../src/start.o
	$(CC) -isystem ../include/socket $(socket_CFLAGS) -o $(OBJDIR)socket.o -c socket.c

$(OBJDIR)start.o: start.c ../src/libc.a ../src/start.o
	$(CC) $(start_CFLAGS) -o $(OBJDIR)start.o -c start.c

$(OBJDIR)stdarg.o: stdarg.c ../src/libc.a ../src/start.o
	$(CC) $(stdarg_CFLAGS) -o $(OBJDIR)stdarg.o -c stdarg.c

$(OBJDIR)stdint.o: stdint.c ../src/libc.a ../src/start.o
	$(CC) $(stdint_CFLAGS) -o $(OBJDIR)stdint.o -c stdint.c

$(OBJDIR)stdio.o: stdio.c ../src/libc.a ../src/start.o
	$(CC) $(stdio_CFLAGS) -o $(OBJDIR)stdio.o -c stdio.c

$(OBJDIR)stdlib.o: stdlib.c ../src/libc.a ../src/start.o
	$(CC) $(stdlib_CFLAGS) -o $(OBJDIR)stdlib.o -c stdlib.c

$(OBJDIR)string.o: string.c ../src/libc.a ../src/start.o
	$(CC) $(string_CFLAGS) -o $(OBJDIR)string.o -c string.c

$(OBJDIR)time.o: time.c ../src/libc.a ../src/start.o
	$(CC) $(time_CFLAGS) -o $(OBJDIR)time.o -c time.c

$(OBJDIR)unistd.o: unistd.c
	$(CC) $(unistd_CFLAGS) -o $(OBJDIR)unistd.o -c unistd.c

clean:
	$(RM) -- $(dlfcn_OBJS) $(errno_OBJS) $(fnmatch_OBJS) $(includes_OBJS) $(langinfo_OBJS) $(netdb_OBJS) $(ptrace_OBJS) $(pwd_OBJS) $(regex_OBJS) $(rt_OBJS) $(select_OBJS) $(setjmp_OBJS) $(signal_OBJS) $(socket_OBJS) $(start_OBJS) $(stdarg_OBJS) $(stdint_OBJS) $(stdio_OBJS) $(stdlib_OBJS) $(string_OBJS) $(time_OBJS) $(tests.log_OBJS) $(unistd_OBJS)
	./tests.sh -c -P "$(PREFIX)" -- "tests.log"

distclean: clean
	$(RM) -- $(TARGETS)

install: $(TARGETS)

uninstall:

.PHONY: all clean distclean install uninstall
