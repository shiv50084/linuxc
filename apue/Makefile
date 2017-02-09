CC=gcc
COMPILE.c=$(CC) $(CFLAGS) $(CPPFLAGS) -c
LINK.c=$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
CFLAGS=-DLINUX -ansi -I$(PWD)/include -Wall -D_GNU_SOURCE $(EXTRA)

PROGS =	shell1 shell2 unlink pipe1 pipe2 popen2

all: $(PROGS)

shell1:	shell1.o errors.o
		$(CC) $(CFLAGS) -o $@ $^

shell2:	shell2.o errors.o
		$(CC) $(CFLAGS) -o $@ $^

unlink:	unlink.o errors.o
		$(CC) $(CFLAGS) -o $@ $^

pipe1:	pipe1.o errors.o
		$(CC) $(CFLAGS) -o $@ $^

pipe2:	pipe2.o errors.o
		$(CC) $(CFLAGS) -o $@ $^

popen2:	popen2.o errors.o
		$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(PROGS) *.o
