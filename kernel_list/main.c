#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct list_head {
	struct list_head *next, *prev;
};

static void __list_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
	__list_add(new, head->prev, head);
}

static inline void list_add(struct list_head *new, struct list_head *head)
{
	__list_add(new, head, head->next);
}

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

#define list_first_entry(ptr, type, member) \
	list_entry((ptr)->next, type, member)

#define list_next_entry(pos, member) \
	list_entry((pos)->member.next, typeof(*(pos)), member)

#define list_for_each_entry(pos, head, member)				\
	for (pos = list_first_entry(head, typeof(*pos), member);	\
	     &pos->member != (head);					\
	     pos = list_next_entry(pos, member))

#define list_prev_entry(pos, member) \
	list_entry((pos)->member.prev, typeof(*(pos)), member)

#define list_last_entry(ptr, type, member) \
	list_entry((ptr)->prev, type, member)

#define list_for_each_entry_reverse(pos, head, member)			\
	for (pos = list_last_entry(head, typeof(*pos), member);		\
	     &pos->member != (head); 					\
	     pos = list_prev_entry(pos, member))

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

	if (reverse)
		list_for_each_entry_reverse(ps, &person_list, list)
			printf("%s[%d]\n", ps->name, ps->number);
	else
		list_for_each_entry(ps, &person_list, list)
			printf("%s[%d]\n", ps->name, ps->number);
}

int main(int argc, char *argv[])
{
	int i;

	/* add player to the list */
	for (i = 0; i < sizeof(players) / sizeof(players[0]); i++)
		add_person(players[i], i, 0);

	check_person_list(0);
	return 0;
}