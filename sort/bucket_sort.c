#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "insert_sort.h"

#define BUCKET_NR 5 /* number of buckets */
#define CHECK_BUCKET

struct Node
{
	int data;
	struct Node *next;
};

struct Bucket
{
	/* number of elements in a bucket */
	int count;

	/* link list head of slot in the bucket */
	struct Node *slots;
};

/*
 * 根据数据的大小将数据分装在不同的桶中
 * 返回桶编号
 */
#define INTERVAL 10
int get_bucket_index(int value)
{
	return value / INTERVAL;
}

/* 打印桶(链表)里的数据 */
void print_bucket(struct Bucket *bucket)
{
	struct Node *cur = bucket->slots;

	while (cur)
	{
		printf("%d ", cur->data);
		cur = cur->next;
	}
}

/* store bucket data to array */
void bucket_pop(struct Bucket *bucket, int array[])
{
	int i = 0;
	struct Node *tmp = bucket->slots;

	while (tmp)
	{
		array[i++] = tmp->data;
		tmp = tmp->next;
	}
}

/* put data back into bucket */
void bucket_push(struct Bucket *bucket, int array[])
{
	int i = 0;
	struct Node *tmp = bucket->slots;

	while (tmp)
	{
		tmp->data = array[i];
		tmp = tmp->next;
		i++;
	}
}

/*
 * 将待排序的数据分装在几个桶中
 * 这里用链表作为描述桶的数据结构
 */
void bucket_sort(int array[], int len)
{
	int i, j;
	struct Bucket *buckets[BUCKET_NR]; /* 所有的桶 */
	struct Node *current;
	int pos;
	int tmp_array[20];

	/* initialize pointers to the buckets */
	for (i = 0; i < BUCKET_NR; i++)
	{
		buckets[i] = (struct Bucket *)malloc(sizeof(struct Bucket *));
		if (NULL == buckets[i])
		{
			printf("Error : no memory\n");
			exit(-1);
		}

		buckets[i]->count = 0;
		buckets[i]->slots = NULL;
	}

	/*
	 * put items into the buckets
	 * creates a link list in each bucket slot
	 */
	for (i = 0; i < len; i++)
	{
		pos = get_bucket_index(array[i]);
		current = (struct Node *)malloc(sizeof(struct Node));
		if (NULL == current)
		{
			printf("Error : no memory\n");
			exit(-1);
		}

		current->data = array[i];
		current->next = buckets[pos]->slots;
		buckets[pos]->slots = current;
		buckets[pos]->count++;
	}

#ifdef CHECK_BUCKET
	/* check what's in each bucket */
	for (i = 0; i < BUCKET_NR; i++)
	{
		printf("Bucket[\"%d\"][%d] : ", i, buckets[i]->count);
		print_bucket(buckets[i]);
		printf("\n");
	}
#endif

	/* sorting bucket using insert sort */
	for (i = 0; i < BUCKET_NR; i++)
	{
		bucket_pop(buckets[i], tmp_array);
		insert_sort(tmp_array, buckets[i]->count);
		bucket_push(buckets[i], tmp_array);
	}

#ifdef CHECK_BUCKET
	/* check what's in each bucket */
	for (i = 0; i < BUCKET_NR; i++)
	{
		printf("Bucket[\"%d\"][%d] : ", i, buckets[i]->count);
		print_bucket(buckets[i]);
		printf("\n");
	}
#endif

	/* put sorted data into origin array */
	for (i = 0, j = 0; i < BUCKET_NR; i++)
	{
		struct Node *tmp;

		tmp = buckets[i]->slots;
		while (tmp)
		{
			array[j++] = tmp->data;
			tmp = tmp->next;
		}
	}
}

int main(int argc, char *argv[])
{
	int len;
	int array[] = {11, 22, 25, -1, 49, 14, 9, 37, 21, 43};

	len = ARRAY_LEN(array);
	show_array(array, len);
	bucket_sort(array, len);
	show_array(array, len);

	return 0;
}
