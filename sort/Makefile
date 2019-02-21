CC=gcc
CFLAGS= -Wall -ftest-coverage -fprofile-arcs

PROGS =	bubbleSort quickSort insertSort shellSort\
		selectSort bucketSort heapSort

all:	$(PROGS)

heapSort: heap_sort.o common.o
		$(CC) $(CFLAGS) -o $@ $^

bucketSort: bucket_sort.o insert_sort.o common.o
		$(CC) $(CFLAGS) -o $@ $^

insertSort: insert_sort.o common.o insert_sort_test.o
		$(CC) $(CFLAGS) -o $@ $^

shellSort: shell_sort.o common.o
		$(CC) $(CFLAGS) -o $@ $^

bubbleSort: bubble_sort.o common.o
		$(CC) $(CFLAGS) -o $@ $^

quickSort: quick_sort.o common.o
		$(CC) $(CFLAGS) -o $@ $^

selectSort: select_sort.o common.o
		$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(PROGS) *.o *.gcda *.gcno *.gcov
