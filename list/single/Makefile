CC=gcc
COMPILE.c=$(CC) $(CFLAGS) $(CPPFLAGS) -c
LINK.c=$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
CFLAGS= -Wall

PROGS =	singlelist

all:	$(PROGS)

$(PROGS):	main.o linklist.o
		$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(PROGS) *.o
