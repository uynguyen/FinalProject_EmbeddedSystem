#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

typedef struct node {
    void* value;
    struct node* next;
} Node;


typedef struct list {
    Node *head;
    Node *tail;
    void (*add_to_head)(struct list, Node*);
    void (*remove_from_head)(struct list);
    Node* (*get_head)(struct list);
    Node* (*get_tail)(struct list);
    void (*add_to_tail)(struct list, Node*);
    void (*remove_from_tail)(struct list);
    int (*is_empty)(struct list);
    
} LinkedList;

void initList(LinkedList*);
Node* create_node(void*);
void add_head(LinkedList, Node*);
void add_tail(LinkedList, Node*);
void remove_head(LinkedList);
void remove_tail(LinkedList);
Node* get_head(LinkedList);
Node* get_tail(LinkedList);
int is_empty(LinkedList);


#endif