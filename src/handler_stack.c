#include <handler_stack.h>

typedef struct handler_stack_node{
	void *handler;
	struct handler_stack_node *next;
} handler_stack;

void push_handler(handler_stack **stack, void* handler)
{
	handler_stack *aux;
	aux = malloc(sizeof(handler_stack));
	aux->handler = handler;
	aux->next = *stack;
	*stack = aux;
}

void pop_handler(handler_stack **stack)
{
	void *handler;
	handler_stack *aux;

	aux = *stack;
	handler = aux->handler;

	*stack = (*stack)->next;

	dlclose(handler);
	free(aux);
}
