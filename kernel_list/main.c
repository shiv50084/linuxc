#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern void add_person(const char *person_name, int number, int to_tail);
extern void check_person_list(int reverse);
extern int delete_person(void);
extern int neighbour_of(void);

int main(int argc, char *argv[])
{
	int ch;
	char name[20];
	int to_tail = 0;
	int number = -1;

	do
	{
		printf("=========kenrle list==========\n");
		printf("(q)uit the system\n");
		printf("(a)dd a player to the list\n");
		printf("(l)ist all players' info\n");
		printf("(r)everse print player's info\n");
		printf("(d)elte a player\n");
		printf("(n)eighbour of\n");
		printf("=========kenrle list==========\n");

		switch (ch)
		{
			case 'a':
				printf("Enter Name:");
				scanf("%s", name);
				printf("Enter Number: ");
				scanf("%d", &number);
				printf("add to tail? default not, <0 | 1>: ");
				scanf("%d", &to_tail);
				add_person(name, number, to_tail);
				break;
			case 'l':
				check_person_list(0);
				break;
			case 'r':
				check_person_list(1);
				break;
			case 'd':
				delete_person();
				break;
			case 'n':
				neighbour_of();
				break;
			default:
				break;
		}

	} while ((ch = getchar()) != 'q');

	return 0;
}
