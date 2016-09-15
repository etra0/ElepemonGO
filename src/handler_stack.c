#include "../lib/handler_stack.h"

typedef struct handler_stack_node{
	void *handler;
	struct handler_stack_node *next;
} handler_stack;

void push_handler(handler_stack **stack, void* handler)
{
	handler_stack *aux;
	aux = *stack;

	*stack = malloc(sizeof(handler_stack));

	(*stack)->handler = handler;
	(*stack)->next = aux;
}

void* pop_handler(handler_stack **stack)
{
	void *handler;
	handler_stack *aux;

	handler = (*stack)->handler;
	aux = *stack;

	*stack = (*stack)->next;
	free(aux);

	return handler;
}