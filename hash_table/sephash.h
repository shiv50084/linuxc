#include "common.h"

#ifndef __SEPHASH__
#define __SEPHASH__

struct ListNode
{
	ElementType Element;
	struct ListNode *Next;
};

/*
 * List *TheLists will be an array ot lists, allocated later
 * The lists use heads (for simplicity), though this wastes space
 * TheLists是链表数组,链表使用带有链表头的链表(虽然让费空间但是更容易实现)
 */
struct HashTable
{
	int TableSize;
	struct ListNode **TheLists;
};

struct HashTable *InitializeTable(int TableSize);
void DestroyTable(struct HashTable *H);
struct ListNode *Find(ElementType Key, struct HashTable *H);
void Insert(ElementType Key, struct HashTable *H);
ElementType Retrieve(struct ListNode *P);
void print_hash_table(struct HashTable *H);
/* Routines such as Delete are MakeEmpty are omitted */

#endif
