#include <stdio.h>
#include "elepemon.h"
#include "inih/ini.h"

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

    if (is_empty(*temporal) || (strcmp(section, (*temporal)->elepemon.name))) {
        actual = push_elepemon(temporal, section);
        if (MATCH(section, "hp")) {
            actual->elepemon.hp = atoi(value);
        }
    } else {
        actual = *temporal;
        if (MATCH(section, "defense")) {
            actual->elepemon.defense = atoi(value);
        } else if (MATCH(section,"type")) {
            actual->elepemon.type = atoi(value);
        } else {
            return 0;  /* unknown section/name, error */
        }
        
    }
    return 1;
}

int main()
{
    // struct elepemon test[2];

    // struct elepemon* address;
    // address = test;

    // init_elepemon(&test[0]);
    // init_elepemon(&test[1]);

    struct elepemon_node *stack = NULL;
    /* Verify if the file was loaded correctly and it parses inmediatly*/
    if (ini_parse("ELEPEMONES", handler, &stack) < 0) {
        printf("Can't load 'ELEPEMONES'\n");
        return 1;
    }

    recorrer(stack);

}
