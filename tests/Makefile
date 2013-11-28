TARGETS	= dlfcn includes langinfo netdb ptrace regex select setjmp signal socket start stdint stdio string time tests.log unistd
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

dlfcn_OBJS = dlfcn.o
dlfcn_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) -isystem ../include/dl $(CFLAGSF) $(CFLAGS)
dlfcn_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

dlfcn: $(dlfcn_OBJS)
	$(CC) -o dlfcn $(dlfcn_OBJS) $(dlfcn_LDFLAGS)

includes_OBJS = includes.o
includes_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
includes_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

includes: $(includes_OBJS)
	$(CC) -o includes $(includes_OBJS) $(includes_LDFLAGS)

langinfo_OBJS = langinfo.o
langinfo_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
langinfo_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

langinfo: $(langinfo_OBJS)
	$(CC) -o langinfo $(langinfo_OBJS) $(langinfo_LDFLAGS)

netdb_OBJS = netdb.o
netdb_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) -isystem ../include/socket $(CFLAGSF) $(CFLAGS)
netdb_LDFLAGS = $(LDFLAGSF) $(LDFLAGS) ../src/socket/libsocket.a

netdb: $(netdb_OBJS)
	$(CC) -o netdb $(netdb_OBJS) $(netdb_LDFLAGS)

ptrace_OBJS = ptrace.o
ptrace_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
ptrace_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

ptrace: $(ptrace_OBJS)
	$(CC) -o ptrace $(ptrace_OBJS) $(ptrace_LDFLAGS)

regex_OBJS = regex.o
regex_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
regex_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

regex: $(regex_OBJS)
	$(CC) -o regex $(regex_OBJS) $(regex_LDFLAGS)

select_OBJS = select.o
select_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
select_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

select: $(select_OBJS)
	$(CC) -o select $(select_OBJS) $(select_LDFLAGS)

setjmp_OBJS = setjmp.o
setjmp_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
setjmp_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

setjmp: $(setjmp_OBJS)
	$(CC) -o setjmp $(setjmp_OBJS) $(setjmp_LDFLAGS)

signal_OBJS = signal.o
signal_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
signal_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

signal: $(signal_OBJS)
	$(CC) -o signal $(signal_OBJS) $(signal_LDFLAGS)

socket_OBJS = socket.o
socket_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
socket_LDFLAGS = $(LDFLAGSF) $(LDFLAGS) ../src/socket/libsocket.a

socket: $(socket_OBJS)
	$(CC) -o socket $(socket_OBJS) $(socket_LDFLAGS)

start_OBJS = start.o
start_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
start_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

start: $(start_OBJS)
	$(CC) -o start $(start_OBJS) $(start_LDFLAGS)

stdint_OBJS = stdint.o
stdint_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
stdint_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

stdint: $(stdint_OBJS)
	$(CC) -o stdint $(stdint_OBJS) $(stdint_LDFLAGS)

stdio_OBJS = stdio.o
stdio_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
stdio_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

stdio: $(stdio_OBJS)
	$(CC) -o stdio $(stdio_OBJS) $(stdio_LDFLAGS)

string_OBJS = string.o
string_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
string_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

string: $(string_OBJS)
	$(CC) -o string $(string_OBJS) $(string_LDFLAGS)

time_OBJS = time.o
time_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
time_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

time: $(time_OBJS)
	$(CC) -o time $(time_OBJS) $(time_LDFLAGS)

tests.log: dlfcn includes langinfo netdb ptrace regex select setjmp signal socket start stdint stdio string time tests.sh unistd
	./tests.sh -P "$(PREFIX)" -- "tests.log"

unistd_OBJS = unistd.o
unistd_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
unistd_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

unistd: $(unistd_OBJS)
	$(CC) -o unistd $(unistd_OBJS) $(unistd_LDFLAGS)

dlfcn.o: dlfcn.c ../src/dl/libdl.a ../src/libc.a ../src/start.o
	$(CC) $(dlfcn_CFLAGS) -c dlfcn.c

includes.o: includes.c ../src/libc.a ../src/start.o
	$(CC) $(includes_CFLAGS) -c includes.c

langinfo.o: langinfo.c ../src/libc.a ../src/start.o
	$(CC) $(langinfo_CFLAGS) -c langinfo.c

netdb.o: netdb.c ../src/libc.a ../src/socket/libsocket.a ../src/start.o
	$(CC) $(netdb_CFLAGS) -c netdb.c

ptrace.o: ptrace.c ../src/libc.a ../src/start.o
	$(CC) $(ptrace_CFLAGS) -c ptrace.c

regex.o: regex.c ../src/libc.a ../src/start.o
	$(CC) $(regex_CFLAGS) -c regex.c

select.o: select.c ../src/libc.a ../src/start.o
	$(CC) $(select_CFLAGS) -c select.c

setjmp.o: setjmp.c ../src/libc.a ../src/start.o
	$(CC) $(setjmp_CFLAGS) -c setjmp.c

signal.o: signal.c ../src/libc.a ../src/start.o
	$(CC) $(signal_CFLAGS) -c signal.c

socket.o: socket.c ../src/libc.a ../src/start.o
	$(CC) -isystem ../include/socket $(socket_CFLAGS) -c socket.c

start.o: start.c ../src/libc.a ../src/start.o
	$(CC) $(start_CFLAGS) -c start.c

stdint.o: stdint.c ../src/libc.a ../src/start.o
	$(CC) $(stdint_CFLAGS) -c stdint.c

stdio.o: stdio.c ../src/libc.a ../src/start.o
	$(CC) $(stdio_CFLAGS) -c stdio.c

string.o: string.c ../src/libc.a ../src/start.o
	$(CC) $(string_CFLAGS) -c string.c

time.o: time.c ../src/libc.a ../src/start.o
	$(CC) $(time_CFLAGS) -c time.c

unistd.o: unistd.c
	$(CC) $(unistd_CFLAGS) -c unistd.c

clean:
	$(RM) -- $(dlfcn_OBJS) $(includes_OBJS) $(langinfo_OBJS) $(netdb_OBJS) $(ptrace_OBJS) $(regex_OBJS) $(select_OBJS) $(setjmp_OBJS) $(signal_OBJS) $(socket_OBJS) $(start_OBJS) $(stdint_OBJS) $(stdio_OBJS) $(string_OBJS) $(time_OBJS) $(tests.log_OBJS) $(unistd_OBJS)

distclean: clean
	$(RM) -- $(TARGETS)

install: $(TARGETS)

uninstall:

.PHONY: all clean distclean install uninstall
