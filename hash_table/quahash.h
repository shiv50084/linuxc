#include "common.h"

#ifndef __QUADHASH__
#define __QUADHASH__

enum KindOfEntry { Legitimate, Empty, Deleted };

struct HashEntry
{
	ElementType Element;
	enum KindOfEntry Info;
};

struct HashTable
{
	int TableSize;
	struct HashEntry *TheCells;
};

struct HashTable *InitializeTable(int TableSize);
void DestroyTable(struct HashTable *H);
int Find(ElementType Key, struct HashTable *H);
void Insert(ElementType Key, struct HashTable *H);
ElementType Retrieve(int pos, struct HashTable *H);
struct HashTable *Rehash(struct HashTable *H);
void print_hash_table(struct HashTable *H);
/* Routines such as Delete are MakeEmpty are omitted */
#endif
