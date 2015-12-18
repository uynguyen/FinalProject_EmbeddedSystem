#include "linkedlist.h"
#include "MyStack.h"
#include "stdint.h"



void init_stack(LinkedList *list)
{
    initList(list);
}

void push_to_stack(LinkedList *list, void* value)
{
    list->add_to_head(*list,create_node(value));
}

void* pop_from_stack(LinkedList *list)
{
    Node* p = list->get_head(*list);
    void* value = p->value;
    list->remove_from_head(*list);
    return value;
}