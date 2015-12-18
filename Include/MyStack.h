

#ifndef __MY_STACK__
#define __MY_STACK__

void init_stack(LinkedList list);

void push_to_stack(LinkedList list, void* value);

void* pop_from_stack(LinkedList list);

#endif