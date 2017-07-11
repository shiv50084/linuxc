CC=gcc
COMPILE.c=$(CC) $(CFLAGS) $(CPPFLAGS) -c
LINK.c=$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
CFLAGS=-DLINUX -ansi -I$(PWD)/include -Wall -D_GNU_SOURCE $(EXTRA)

PROGS =	server_wrap client_wrap server_ver1 client_ver1

all: $(PROGS)

server_ver1:	tcp_server.o
		$(CC) $(CFLAGS) -o $@ $^

client_ver1:	tcp_client.o
		$(CC) $(CFLAGS) -o $@ $^

server_wrap:	tcp_server_wrap.o wrap.o
		$(CC) $(CFLAGS) -DUSE_RW -o $@ $^

client_wrap:	tcp_client_wrap.o wrap.o
		$(CC) $(CFLAGS) -DUSE_RW -o $@ $^

clean:
	rm -f $(PROGS) *.o
