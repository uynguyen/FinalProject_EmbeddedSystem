#include "linkedlist.h"
#include "MyStack.h"
#include "stdint.h"



void init_stack(LinkedList list)
{
    initList(list);
}

void push_to_stack(LinkedList list, void* value)
{
    add_head(list,create_node(value));
}

void* pop_from_stack(LinkedList list)
{
    Node* p = get_head(list);
    void* value = p->value;
    remove_head(list);
    return value;
}