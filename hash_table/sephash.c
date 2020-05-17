#include "fatal.h"
#include "sephash.h"
#include <stdlib.h>

/* Return next prime; assume N >= 10 */
static int NextPrime(int N)
{
	int i;

	if (N % 2 == 0)
		N++;
	for (;; N += 2)
	{
		for (i = 3; i * i <= N; i +=2)
			if (N % i == 0)
				goto ContOuter;

		return N;
ContOuter:;
	}
}

/*
 * Hash function for integers
 * return the slot number accroding to the input key
 */
int Hash(ElementType Key, int TableSize)
{
	return Key % TableSize;
}

struct HashTable *InitializeTable(int TableSize)
{
	struct HashTable *H;
	int i;

	if (TableSize < MinTableSize)
	{
		Error("Table size too smale");
		return NULL;
	}
	printf("Initialize table size %d\n", TableSize);

	/* Allocate the table */
	H = malloc(sizeof(struct HashTable));
	if (NULL == H)
		FatalError("Out of memory");

	H->TableSize = NextPrime(TableSize);

	/*
	 * Allocate array of lists
	 * 每个slot的第一个元素都是链表头
	 * 因为这里使用的带有链表头的链表
	 */
	H->TheLists = malloc(sizeof(struct ListNode *) * H->TableSize);
	if (NULL == H->TheLists)
		FatalError("Out of memory");

	/* Allocate list headers */
	for (i = 0; i < H->TableSize; i++)
	{
		H->TheLists[i] = malloc(sizeof(struct ListNode));
		if (NULL == H->TheLists[i])
			FatalError("Out of memroy");
		else
			H->TheLists[i]->Next = NULL;
	}

	return H;
}

/*
 * Find the position of the Key in the hashtoble
 * return NULL if the key is not in the hashtable
 * return the position(ListNode) if key already exist
 */
struct ListNode *Find(ElementType Key, struct HashTable *H)
{
	struct ListNode *head;
	struct ListNode *tmp;

	head = H->TheLists[Hash(Key, H->TableSize)];
	tmp = head->Next;
	while (tmp != NULL && tmp->Element != Key)
		tmp = tmp->Next;

	return tmp;
}

void Insert(ElementType Key, struct HashTable *H)
{
	struct ListNode *pos;
	struct ListNode *head;
	struct ListNode *new_cell;

	/* find the appropriate position */
	pos = Find(Key, H);
	if (NULL == pos) /* key is not in HashTable */
	{
		new_cell = malloc(sizeof(struct ListNode));
		if (NULL == new_cell)
			FatalError("Out of memory");
		else
		{
			/* insert in the front */
			head = H->TheLists[Hash(Key, H->TableSize)];
			new_cell->Next = head->Next;
			new_cell->Element = Key;
			head->Next = new_cell;
		}
	}
}

ElementType Retrieve(struct ListNode *p)
{
	return p->Element;
}

void DestroyTable(struct HashTable *H)
{
	int i;
	struct ListNode *head;
	struct ListNode *tmp;

	for (i = 0; i < H->TableSize; i++)
	{
		head = H->TheLists[i];

		while (head != NULL)
		{
			tmp = head->Next;
			free(head);
			head = tmp;
		}
	}

	free(H->TheLists);
	free(H);
}

void print_hash_table(struct HashTable *H)
{
	int i;
	struct ListNode *p;

	for (i = 0; i < H->TableSize; i++)
	{
		p = H->TheLists[i]->Next;
		printf("Slot: [%d] ", i);
		while (p != NULL)
		{
			printf("%d, ", p->Element);
			p = p->Next;
		}
		printf("\n");
	}
}
