CC=gcc
COMPILE.c=$(CC) $(CFLAGS) $(CPPFLAGS) -c
LINK.c=$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
CFLAGS= -Wall -lpthread

PROGS = accountest detach ignore_sig sig2main\
		pj1 pj2 race

all:	$(PROGS)

accountest:	account.o account_test.o
		$(CC) $(CFLAGS) -o $@ $^

detach:	detach.o
		$(CC) $(CFLAGS) -o $@ $^

ignore_sig: main_ignore_sub_sig.o
		$(CC) $(CFLAGS) -o $@ $^

sig2main:	sub_sig2_main.o
		$(CC) $(CFLAGS) -o $@ $^

pj2:	pjoin2.o
		$(CC) $(CFLAGS) -o $@ $^

pj1:	pjoin.o
		$(CC) $(CFLAGS) -o $@ $^

race:	race.o
		$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(PROGS) *.o a.out
