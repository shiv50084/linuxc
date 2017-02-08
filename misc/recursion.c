#include <stdio.h>

#define LEN 6
char buf[LEN] = {'o', 'o', 't', 'n', 'e', 'g'};

void print_backward(int pos)
{
	if (pos == LEN)
		return;

	print_backward(pos + 1);
	putchar(buf[pos]);
}

int main(int argc, char **argv)
{
	print_backward(0);
	putchar('\n');
	return 0;
}
