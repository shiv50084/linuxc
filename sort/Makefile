CC=gcc
CFLAGS= -Wall -ftest-coverage -fprofile-arcs

PROGS =	bubbleSort quickSort insertSort shellSort

all:	$(PROGS)

insertSort: insert_sort.o common.o
		$(CC) $(CFLAGS) -o $@ $^

shellSort: shell_sort.o common.o
		$(CC) $(CFLAGS) -o $@ $^

bubbleSort: bubble_sort.o common.o
		$(CC) $(CFLAGS) -o $@ $^

quickSort: quick_sort.o common.o
		$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(PROGS) *.o *.gcda *.gcno *.gcov
