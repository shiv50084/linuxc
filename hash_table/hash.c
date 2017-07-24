#include "hash.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * 哈希函数(数据存放的依据)
 * 根据KEY值来生成相应的槽号
 * 这里把槽号分为0~9
 * @PARAMETER	key
 * @RETURN return slot number
 */
int hash_function(int key)
{
	return key % 10;
}

/*
 * 根据节点里要存储的数据构造一个存储节点
 */
NODE* make_node(PI pi)
{
	NODE *n = NULL;

	n = malloc(sizeof(NODE));
	memcpy(&n->pi, &pi, sizeof(pi));
	n->next = NULL;

	return n;
}

/*
 * 将数据插入到HASH TABLE
 * 找到数据对应的槽号
 * 把数据插入到槽号对应的链表里
 * @PARAMETER 插入的数据节点
 */
void insert_data_into_hash(HASH_TABLE* pHashTbl, NODE *n)
{
	int slot;

	/*  根据哈希函数找到槽号 */
	slot = hash_function(n->pi.number);

	/*
	 * 把数据节点插入到槽号对应的链表里
	 * 这里实质就是链表插入操作
	 * pHashTbl->value[slot]是链表头
	 */
	n->next = pHashTbl->value[slot];
	pHashTbl->value[slot] = n;
}

/*
 * @RETURN 返回对应槽号的链表头
 */
LIST_HEAD* find_slot_list_head(HASH_TABLE* pHashTbl, int number)
{
	int slot;

	/*  根据哈希函数找到槽号 */
	slot = hash_function(number);

	return pHashTbl->value[slot];
}

void show_hash_table(HASH_TABLE* pHashTbl)
{
	int i;
	NODE *tmpSlot;

	/* 遍历所有的槽位 */
	for (i = 0; i < SLOTS; i++)
	{
		/* 给定的数据并没有填充所有的slot */
		if (!pHashTbl->value[i])
			continue;

		tmpSlot = pHashTbl->value[i];
		printf("Slot[%d] : ", i);
		while (tmpSlot)
		{
			printf("%s\t", (tmpSlot->pi).name);
			tmpSlot = tmpSlot->next;
		}
		printf("\n");
	}
}
