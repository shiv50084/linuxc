#include "hash.h"
#include <stdio.h>

PI playerInfo[] = {
	{1, "jordan"},
	{2, "kobe"},
	{3, "jame"},
	{5, "jim"},
	{4, "tom"},
	{6, "jack"},
	{22, "brant"},
};

int main(int argc, char *argv[])
{
	int i;
	int input;
	LIST_HEAD *list_head;
	NODE *tmpNode;

	HASH_TABLE HashTable;

	/* 初始化哈希表里的每个槽位对应的链表头为空 */
	for (i = 0; i < sizeof(playerInfo) / sizeof(playerInfo[0]); i++)
		HashTable.value[i] = NULL;

	/* 把数据插入哈希表 */
	for (i = 0; i < sizeof(playerInfo) / sizeof(playerInfo[0]); i++)
	{
		tmpNode = make_node(playerInfo[i]);
		insert_data_into_hash(&HashTable, tmpNode);
	}

	printf("input a number[0-9]:");
	scanf("%d", &input);
	if (input > 9 || input < 0)
	{
		printf("Input error!!!\n");
		return -1;
	}
	list_head = find_slot_list_head(&HashTable, input);
	if (!list_head)
	{
		printf("no this player!!!\n");
		return -1;
	}

	while (list_head)
	{
		printf("name is: %s\n", list_head->pi.name);
		list_head = list_head->next;
	}
	return 0;
}
