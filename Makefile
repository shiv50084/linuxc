CC=gcc
COMPILE.c=$(CC) $(CFLAGS) $(CPPFLAGS) -c
LINK.c=$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
CFLAGS= -Wall

PROGS =	skeleton

all:	$(PROGS)

$(PROGS):	foo.o bar.o
		$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(PROGS) *.o
