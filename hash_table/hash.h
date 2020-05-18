#ifndef _HASH_H_
#define _HASH_H_

/* 假设有10个槽 */
#define SLOTS	10

/*
 * 要存储的信息
 * 球员的号码和名字
 */
typedef struct PlayerInfo {
	int number;
	char name[10];
}PI;

/*
 * 存储在哈希表里对应槽号链表里的节点
 */
typedef struct _NODE
{
	PI pi;
	struct _NODE* next;
}NODE, LIST_HEAD;

/*
 * 哈希表就是一个指针数组
 * 数组中的每一个指针都是一个链表头指针
 * 每一个链表称为一个槽
 */
typedef struct _HASH_TABLE
{
	NODE* value[SLOTS];
}HASH_TABLE;

extern NODE* make_node(PI pi);
extern void insert_data_into_hash(HASH_TABLE* pHashTbl, NODE *n);
extern LIST_HEAD* find_slot_list_head(HASH_TABLE* pHashTbl, int number);
void show_hash_table(HASH_TABLE* pHashTbl);
#endif
