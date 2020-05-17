#include "sephash.h"
#include <stdio.h>

#define NumItems 400

int main(int argc, char *argv[])
{
	struct HashTable *H;
	struct ListNode *P;
	int i;
	int j = 0;
	int CurrentSize = 13;

	H = InitializeTable(CurrentSize);

	for (i = 0; i < NumItems; i++, j += 71)
		Insert(j, H);

	for (i = 0, j = 0; i < NumItems; i++, j += 71)
		if ((P = Find(j, H)) == NULL || Retrieve(P) != j)
			printf("Error at %d\n", j);

	print_hash_table(H);

	return 0;
}
