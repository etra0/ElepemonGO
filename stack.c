#include "elepemon.h"

int is_empty(struct elepemon_node* stack)
{
    return stack == NULL;
}

struct elepemon_node* push_elepemon(struct elepemon_node** stack, const char* name)
{
    struct elepemon_node* aux;
    aux = *stack;

    *stack = malloc(sizeof(struct elepemon_node));
    init_elepemon(&((*stack)->elepemon));
    (*stack)->elepemon.name = strdup(name);
    (*stack)->next = aux;

    return *stack;
}

