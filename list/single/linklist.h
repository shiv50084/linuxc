#ifndef LINKLIST_H
#define LINKLIST_H

struct node {
	unsigned char item;
	struct node *next;
};

struct node* make_node(unsigned char item);
void free_node(struct node *p);
struct node* search(unsigned char key);
void delete(struct node* p);
void delete_plus(struct node *p);
void traverse(void (*visit)(struct node*));
void destroy(void);
void push(struct node *p);
struct node* pop(void);
void insert(struct node* p);

#endif

