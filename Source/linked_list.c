#include "linkedlist.h"




void initList(LinkedList list)
{
    list.head = 0;
    list.tail = 0;
}

Node* create_node(void* value)
{
    Node* p;
    void* val;
    p = (Node*)malloc(sizeof(Node));
    val = (void *)malloc(sizeof(value));
    val = value;
    p->next = 0;
    p->value = val;
    return p;
}

void add_head(LinkedList list, Node* elm)
{
    if (is_empty(list))
    {
        list.head = list.tail = elm;
    }
    else
    {
        Node* head = list.head;
        list.head = elm;
        list.head->next = head;
    }
}

void add_tail(LinkedList list, Node* elm)
{
        if (is_empty(list))
    {
        list.head = list.tail = elm;
    }
    else
    {
        list.tail->next = elm;
        list.tail = list.tail->next;
    }
}

void remove_head(LinkedList list)
{
    if (is_empty(list) == 1)
    {
        Node* p = list.head;
        list.head = p->next;
        free(p->value);
        free(p);
    }
}


Node* get_head(LinkedList list)
{
    return list.head;
}

Node* get_tail(LinkedList list)
{
    return list.tail;
}

int is_empty(LinkedList list)
{
    return list.head == 0 ? 1: 0;
}