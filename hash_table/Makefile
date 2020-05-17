PROGS = demo1 sepHash

all:	$(PROGS)

demo1 : hash.o main.o
	$(CC) -o $@ $^

sepHash : sepHashTest.c sephash.c
	$(CC) -o $@ $^

clean:
	rm *.o $(PROGS)
