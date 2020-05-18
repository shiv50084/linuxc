#include <stdio.h>
#include <stdlib.h>

#define Error( Str )        FatalError( Str )
#define FatalError( Str )   fprintf( stderr, "%s\n", Str ), exit( 1 )

typedef int ElementType;
#define MinTableSize (10)

/* Return next prime; assume N >= 10 */
static inline int NextPrime(int N)
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
static int Hash(ElementType Key, int TableSize)
{
	return Key % TableSize;
}
