#include "elepemon.h"

int is_empty(struct elepemon_node* stack)
{
    return stack == NULL;
}

struct elepemon* get_elepemon( struct elepemon_node* stack, const char* name)
{
    struct elepemon_node* ptr = stack;

    while( !(is_empty (ptr)) ){
        if ( ptr -> elepemon.name == name ){
            return elepemon;
        }
        ptr = ptr -> next;
    }

    return NULL;
}

void free_elepemon_stack(struct elepemon_node* stack)
{
    while( !(is_empty(stack)) ){
        struct elepemon_node* aux;
        free_elepemon( stack->elepemon );
        aux = stack;
        stack = stack-> next;
        free(aux);
    }

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

