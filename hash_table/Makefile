PROGS = demo1 sepHash quaHash

all:	$(PROGS)

demo1 : hash.o main.o
	$(CC) -o $@ $^

sepHash : sepHashTest.o sephash.o
	$(CC) -o $@ $^

quaHash : quaHashTest.o quahash.o
	$(CC) -o $@ $^

clean:
	rm *.o $(PROGS)
