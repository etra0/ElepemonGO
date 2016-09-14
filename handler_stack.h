#ifndef HANDLER_STACK_H
#define HANDLER_STACK_H
#include "elepemon.h"

typedef struct handler_stack_node handler_stack;

void push_handler(handler_stack **stack, void* handler);

void* pop_handler(handler_stack **stack);

#endif // !HANDLER_STACK_H