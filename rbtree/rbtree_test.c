#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

#define CHECK_INSERT 1
#define CHECK_DELETE 1
#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )

typedef int Type;

struct my_node {
    struct rb_node rb_node;
    Type key;
};

/* find out node which value equal to key */
struct my_node *my_search(struct rb_root *root, Type key)
{
    struct rb_node *rbnode = root->rb_node;

    while (rbnode != NULL)
    {
        struct my_node *mynode = container_of(rbnode, struct my_node, rb_node);

        if (key < mynode->key)
            rbnode = rbnode->rb_left;
        else if (key > mynode->key)
            rbnode = rbnode->rb_right;
        else
            return mynode;
    }

    return NULL;
}

/* insert a node which value equal to key to the rbtree */
int my_insert(struct rb_root *root, Type key)
{
    struct my_node *mynode;
    struct rb_node **tmp = &(root->rb_node), *parent = NULL;

    /* Figure out where to put new node */
    while (*tmp)
    {
        struct my_node *my = container_of(*tmp, struct my_node, rb_node);

        parent = *tmp;
        if (key < my->key)
            tmp = &((*tmp)->rb_left);
        else if (key > my->key)
            tmp = &((*tmp)->rb_right);
        else
            return -1;
    }

	/* out of memeory, failed and return */
    if ((mynode = malloc(sizeof(struct my_node))) == NULL)
        return -1;

    mynode->key = key;

    /* Add new node and rebalance tree. */
    rb_link_node(&mynode->rb_node, parent, tmp);
    rb_insert_color(&mynode->rb_node, root);

    return 0;
}

/* Delete the node which value equal to key */
void my_delete(struct rb_root *root, Type key)
{
    struct my_node *mynode;

	/* find out the node which value equal to key */
    if ((mynode = my_search(root, key)) == NULL)
        return ;

	/* erase the node from rbtree */
    rb_erase(&mynode->rb_node, root);
    free(mynode);
}

/* print out rbtree */
static void print_rbtree(struct rb_node *tree, Type key, int direction)
{
	/*
	 * find out the current node's parent node
	 * rb_parent(tree) return a parent node point
	 * container_of find out the parent's data struct
	 */
	struct my_node *parent = container_of(rb_parent(tree), struct my_node, rb_node);

    if(tree != NULL)
    {
		/* root node */
        if(0 == direction)
            printf("%2d(B) is root\n", key);
        else /* branch node */
            printf("%2d(%s) is %2d's %6s child\n", key, rb_is_black(tree) ? "B":"R", parent->key, direction == 1 ? "right" : "left");

        if (tree->rb_left)
            print_rbtree(tree->rb_left, rb_entry(tree->rb_left, struct my_node, rb_node)->key, -1);

        if (tree->rb_right)
            print_rbtree(tree->rb_right,rb_entry(tree->rb_right, struct my_node, rb_node)->key,  1);
    }
}

void my_print(struct rb_root *root)
{
    if (root!=NULL && root->rb_node!=NULL)
        print_rbtree(root->rb_node, rb_entry(root->rb_node, struct my_node, rb_node)->key,  0);
}

int main(int argc, char *argv[])
{
    int raw_data[] = {10, 40, 30, 60, 90, 70, 20, 50, 80};
    int i;
	int len;
    struct rb_root mytree = RB_ROOT;

	len = LENGTH(raw_data);

    printf("== 原始数据: ");
    for(i = 0; i < len; i++)
        printf("%d ", raw_data[i]);
    printf("\n");

    for(i = 0; i < len; i++)
    {
        my_insert(&mytree, raw_data[i]);
#if CHECK_INSERT
        printf("== 添加节点: %d\n", raw_data[i]);
        printf("== 树的详细信息: \n");
        my_print(&mytree);
        printf("\n");
#endif
    }

#if CHECK_DELETE
    for(i = 0; i < len; i++)
	{
        my_delete(&mytree, raw_data[i]);

        printf("== 删除节点: %d\n", raw_data[i]);
        printf("== 树的详细信息: \n");
        my_print(&mytree);
        printf("\n");
    }
#endif

	return 0;
}
