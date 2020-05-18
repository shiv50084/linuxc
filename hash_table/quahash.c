#include "quahash.h"
#include <stdlib.h>

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
	 * Allocate array of Cells
	 */
	H->TheCells = malloc(sizeof(struct HashEntry) * H->TableSize);
	if (NULL == H->TheCells)
		FatalError("Out of memory");

	for (i = 0; i < H->TableSize; i++)
		H->TheCells[i].Info = Empty;

	return H;
}

/* Find the position of the Key in the hashtoble */
int Find(ElementType Key, struct HashTable *H)
{
	int CurrentPos;
	int CollisionNum = 0;

	CurrentPos = Hash(Key, H->TableSize);

	/* Yep, we got collision, let's resolve it */
	while (H->TheCells[CurrentPos].Info != Empty &&
			H->TheCells[CurrentPos].Element != Key)
	{
		CurrentPos += 2 * ++CollisionNum - 1;
		if (CurrentPos >= H->TableSize)
			CurrentPos -= H->TableSize;
	}

	return CurrentPos;
}

void Insert(ElementType Key, struct HashTable *H)
{
	int pos;

	pos = Find(Key, H);
	if (H->TheCells[pos].Info != Legitimate)
	{
		/* it'is fine to insert here */
		H->TheCells[pos].Info = Legitimate;
		H->TheCells[pos].Element = Key;
	}
}

struct HashTable *Rehash(struct HashTable *H)
{
	int i, oldSize;
	struct HashEntry *oldCells;

	oldCells = H->TheCells;
	oldSize = H->TableSize;

	H = InitializeTable(2 * oldSize);

	/* scan through old table, reinserting into new */
	for (i = 0; i < oldSize; i++)
		if (oldCells[i].Info == Legitimate)
			Insert(oldCells[i].Element, H);

	free(oldCells);

	return H;
}

ElementType Retrieve(int pos, struct HashTable *H)
{
	return H->TheCells[pos].Element;
}

void DestroyTable(struct HashTable *H)
{
	free(H->TheCells);
	free(H);
}

void print_hash_table(struct HashTable *H)
{
	int i;
	int j = 0;

	for (i = 0; i < H->TableSize; i++)
	{
		/* print out the cell only legitimate */
		if (H->TheCells[i].Info == Legitimate)
		{
			printf("%03d : Slot[%04d] = %d\n",j , i, H->TheCells[i].Element);
			j++;
		}
	}
}
