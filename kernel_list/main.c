#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

# define POISON_POINTER_DELTA 0
#define LIST_POISON1  ((void *) 0x100 + POISON_POINTER_DELTA)
#define LIST_POISON2  ((void *) 0x200 + POISON_POINTER_DELTA)

struct list_head {
	struct list_head *next, *prev;
};

static inline void __list_add(struct list_head *new,
		struct list_head *prev,
		struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

typedef __signed__ char __s8;
typedef unsigned char __u8;

typedef __signed__ short __s16;
typedef unsigned short __u16;

typedef __signed__ int __s32;
typedef unsigned int __u32;

typedef __signed__ long __s64;
typedef unsigned long __u64;

/* The "volatile" is due to gcc bugs */
#define barrier() __asm__ __volatile__("": : :"memory")

static __always_inline void __write_once_size(volatile void *p, void *res, int size)
{
	switch (size) {
	case 1: *(volatile __u8 *)p = *(__u8 *)res; break;
	case 2: *(volatile __u16 *)p = *(__u16 *)res; break;
	case 4: *(volatile __u32 *)p = *(__u32 *)res; break;
	case 8: *(volatile __u64 *)p = *(__u64 *)res; break;
	default:
		barrier();
		__builtin_memcpy((void *)p, (const void *)res, size);
		barrier();
	}
}

#define __force
#define WRITE_ONCE(x, val) \
({							\
	union { typeof(x) __val; char __c[1]; } __u =	\
		{ .__val = (__force typeof(x)) (val) }; \
	__write_once_size(&(x), __u.__c, sizeof(x));	\
	__u.__val;					\
})

static inline void __list_del(struct list_head * prev, struct list_head * next)
{
	next->prev = prev;
	WRITE_ONCE(prev->next, next);
}

static inline void list_del(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
	entry->next = LIST_POISON1;
	entry->prev = LIST_POISON2;
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
