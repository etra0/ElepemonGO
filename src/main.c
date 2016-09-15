#include <stdio.h>
#include "../lib/elepemon.h"
#include "../inih/ini.h"

#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0

// temporal
void recorrer(struct elepemon_node* stack);

static int handler(void* elepemon, const char* section, const char* name,
                   const char* value)
{
    
    struct elepemon_node **temporal;
    temporal = (struct elepemon_node **) elepemon;

    struct elepemon_node *actual;

    /* Se pregunta si el stack esta vacio O si siguen leyendo el mismo elepemon,
     * ya que si no, se creaba un elepemon por cada atributo
     */

    if (is_empty(*temporal) || (strcmp(section, (*temporal)->elepemon.name)))
        actual = push_elepemon(temporal, section);
    else
        actual = *temporal;

    if (MATCH(section, "hp")) {
        actual->elepemon.hp = atoi(value);
    } else if (MATCH(section, "defense")) {
        actual->elepemon.defense = atoi(value);
    } else if (MATCH(section,"type")) {
        actual->elepemon.type = atoi(value);
    } else if (MATCH(section, "power")) {
        /* Se envia a NULL porque suponemos que siempre habra un valor valido */
        actual->elepemon.power = strtol(value, NULL, 10);
    } else if (MATCH(section, "attacks")) {
        actual->elepemon.attack.attack_ids = get_attack_ids(value, &(actual->elepemon.attack.attack_count));
    } else {
        return 0;  /* unknown section/name, error */
    }
    return 1;
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        printf("No se han ingresado los suficientes parametros");
        return -1;
    }

    char *elepemones_filename = strdup(argv[2]);
    char *attack_folder = strdup(argv[1]);

    struct elepemon_node *main_stack = NULL;
    // Stack de los jugadores, que se sacaran del main_stack.
    struct elepemon_node *stack1 = NULL;
    struct elepemon_node *stack2 = NULL;

    int fin = 0;

    /* Verify if the file was loaded correctly and it parses inmediatly*/
    if (ini_parse(elepemones_filename, handler, &main_stack) < 0) {
        printf("Can't load 'ELEPEMONES'\n");
        return 1;
    }

    recorrer(main_stack);

    move_stack_node(&main_stack, &stack1, 3);    
    printf("STACK PRINCIPAL:\n");
    recorrer(main_stack);

    printf("STACK1:\n");
    recorrer(stack1);

    // load_attacks("attacks", get_elepemon(stack, "Charmander"));
    // load_attacks("attacks", get_elepemon(stack, "Charizard"));
    // load_attacks("attacks", get_elepemon(stack, "asfsf"));
    

    // unload_attacks();

    // recorrer(stack); 

    // print_elepemon(&(stack->elepemon));
    // printf("FREE\n");
    // free_elepemon_stack(stack);
    // stack = NULL;
    // print_elepemon(&(stack->elepemon));
    // // recorrer(stack);    

    return 0;

}
