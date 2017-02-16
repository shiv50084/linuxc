CC=gcc
COMPILE.c=$(CC) $(CFLAGS) $(CPPFLAGS) -c
LINK.c=$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
CFLAGS=-DLINUX -ansi -I$(PWD)/include -Wall -D_GNU_SOURCE $(EXTRA)

PROGS =	shell1 shell2 unlink pipe1 pipe2 pipe4 popen1 \
	popen2 myuclc add2 nobuffer_io std_io

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

pipe4:	pipe4.o errors.o
		$(CC) $(CFLAGS) -o $@ $^

popen1:	popen1.o errors.o
		$(CC) $(CFLAGS) -o $@ $^

popen2:	popen2.o errors.o
		$(CC) $(CFLAGS) -o $@ $^

myuclc:	myuclc.o errors.o
		$(CC) $(CFLAGS) -o $@ $^

add2:	add2.o errors.o
		$(CC) $(CFLAGS) -o $@ $^

nobuffer_io:	nobuffer_io.o errors.o
		$(CC) $(CFLAGS) -o $@ $^

std_io:	std_io.o errors.o
		$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(PROGS) *.o
