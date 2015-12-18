#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

typedef struct node {
    void* value;
    struct node* next;
} Node;


typedef struct list {
    Node* head;
    Node* tail;
} LinkedList;

void initList(LinkedList);
Node* create_node(void*);
void add_head(LinkedList, Node*);
void add_tail(LinkedList, Node*);
void remove_head(LinkedList);
Node* get_head(LinkedList);
Node* get_tail(LinkedList);
int is_empty(LinkedList);


#endif