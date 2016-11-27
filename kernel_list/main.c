#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "klist.h"

static LIST_HEAD(person_list);
struct person
{
	char name[20];
	int number;
	struct list_head list;
};

/* add a person to the person list */
void add_person(const char *person_name, int number, int to_tail)
{
	struct person *tmp;
	tmp = malloc(sizeof(struct person));
	if (NULL == tmp)
	{
		printf("error\n");
		return;
	}

	tmp->number = number;
	strcpy(tmp->name, person_name);

	if (to_tail)
		list_add_tail(&tmp->list, &person_list);
	else
		list_add(&tmp->list, &person_list);
}

const char *players[] = {
	"jordan",
	"eminem",
	"shady"
};

void check_person_list(int reverse)
{
	struct person *ps;

	printf("----------PLAYER'S INFO--------------\n");
	if (reverse)
		list_for_each_entry_reverse(ps, &person_list, list)
			printf("%s[%d]\n", ps->name, ps->number);
	else
		list_for_each_entry(ps, &person_list, list)
			printf("%s[%d]\n", ps->name, ps->number);
	printf("----------PLAYER'S INFO--------------\n");
}

void delete_person(void)
{
	struct person *ps;
	char name[20];
	int delete_person_found = 0;

	printf("Enter Name :");
	scanf("%s", name);
	list_for_each_entry(ps, &person_list, list) {
		if (!strcmp(name, ps->name))
		{
			delete_person_found = 1;
			break;
		}
	}

	if (delete_person_found)
		list_del(&ps->list);

	printf("No this guy :(\n");
}

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
			default:
				break;
		}

	} while ((ch = getchar()) != 'q');

	return 0;
}
