#include <stdio.h>
#include "../lib/elepemon.h"
#include "../inih/ini.h"
#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
#define input printf("\n> ")

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
        parse_type(value, &(actual->elepemon.type));
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

    /* Stack de los jugadores, que se sacaran del main_stack. */
    struct elepemon_node *stack[2] = {NULL, NULL};

    /* Stack en el cual se almacenaran los elepemones muertos,
     * Para despues liberarlos con mayor facilidad */
    struct elepemon_node *deadpool = NULL;

    /* el indice 0 corresponde al atacante, el 1 al defensor */
    struct elepemon *elepemon_selected[2] = {NULL, NULL};

    char *player_names[2], buffer[50];

    int end = 0, choices, elepemones_per_player, i, j;
    int quantity;

    /* Verify if the file was loaded correctly and it parses inmediatly*/
    if (ini_parse(elepemones_filename, handler, &main_stack) < 0) {
        printf("Can't load 'ELEPEMONES'\n");
        return 1;
    }

    quantity = get_stack_size(main_stack);

    printf("Bienvenidos a un nuevo elepeduelo\n");
    printf("Ingrese el nombre del primer entrenador: ");
    input; scanf("%s", buffer);
    player_names[0] = strdup(buffer);

    printf("Ingrese el nombre del segundo entrenador: ");
    input; scanf("%s", buffer);
    player_names[1] = strdup(buffer);

    do {
    printf("Ingrese la cantidad de elepemones:\n");
    input; scanf("%d", &elepemones_per_player);
    if (elepemones_per_player > quantity/2)
        printf("Solo tenemos %d elepemones, intente nuevamente, ", quantity);
    } while (elepemones_per_player > quantity/2);


    for (i = 0; i < 2; i++) {
        printf("%s, elije tus elepemones:\n", player_names[i]);
        for (j = 0; j < elepemones_per_player; j++) {
            do {
            print_stack(main_stack);

            input; scanf("%d", &choices);

            if (choices <= 0 || (choices > quantity))
                printf("Ingrese un numero valido!\n");
            else
                quantity = get_stack_size(main_stack);

            } while ((choices <= 0) || (choices > quantity));

            move_stack_node(&main_stack, &stack[i], choices);
        }
    }

    printf("Elepemones %s:\n",player_names[0]);
    print_stack(stack[0]);
    printf("\n---------\n");
    printf("Elepemones %s:\n", player_names[1]);
    print_stack(stack[1]);
    printf("\n---------\n");

    printf("IT'S TIME TO DU-DU-DU-DU-DUEL!!!11!!uno!\n");

    i = 0;
    while (!end) {
        do {
            printf("%s, que elepemon ataca?", player_names[i]);
            input; scanf("%s", buffer);
            if (strcmp(buffer, "*LISTA*") == 0) {
                printf("Actualmente, tienes estos elepemones:\n");
                print_stack(stack[i]);
                printf("\n\n");
                elepemon_selected[0] = NULL;
                continue;
            }
            elepemon_selected[0] = get_elepemon(stack[i], buffer);
            if (elepemon_selected[0] == NULL)
                printf("No tienes ese elepemon!, ");
        } while (elepemon_selected[0] == NULL);

        do {
            printf("Que ataque usara?");
            input; scanf("%s", buffer);

            if (strcmp(buffer, "*ATAQUES*") == 0) {
                printf("El elepemon %s tiene estos ataques:\n", elepemon_selected[0]->name);
                read_attacks(elepemon_selected[0]);
                printf("\n\n");
                choices = -1;
                continue;
            }
            /* reutilizacion de choices, en este caso, actua como booleano */
            choices = verify_attack(elepemon_selected[0], buffer);
            if (choices == -1) {
                printf("%s no tiene %s!, ", elepemon_selected[0]->name, buffer);
            }
        } while (choices == -1);

        load_attacks(attack_folder, elepemon_selected[0]);

        do {
            printf("%s, a que elepemon ataca?", elepemon_selected[0]->name);
            input; scanf("%s", buffer);

            /* Comando para verificar que elepemones tiene el enemigo */
            if (strcmp(buffer, "*LISTA*") == 0) {
                printf("Actualmente, el enemigo tiene estos elepemones:\n");
                print_stack(stack[!i]);
                printf("\n\n");
                elepemon_selected[1] = NULL;
                continue;
            }

            /* Debido a que son solo 2 jugadores, el contrapuesto es el negado del actual */
            elepemon_selected[1] = get_elepemon(stack[!i], buffer);
            if (elepemon_selected[1] == NULL)
                printf("El enemigo no tiene ese elepemon!, ");

        } while (elepemon_selected[1] == NULL);

        check_attack(elepemon_selected[0]->attack.attacks[choices](elepemon_selected[0], elepemon_selected[1]));

        if (elepemon_selected[1]->hp <= 0) {
            printf("El elepemon %s ha muerto! :(\n", elepemon_selected[1]->name);
            move_stack_node(&stack[!i], &deadpool, find_index(stack[!i], elepemon_selected[1]));
        }

        if (get_stack_size(stack[!i]) == 0) {
            printf("El jugador %s se ha quedado sin elepemones.\n\n", player_names[!i]);
            printf("Felicidades %s, has ganado!", player_names[i]);
            end = 1;
        }

        i = !i;
    }

    unload_attacks();
    free_elepemon_stack(main_stack);
    free_elepemon_stack(stack[0]); free_elepemon_stack(stack[1]);
    free_elepemon_stack(deadpool);
    main_stack = NULL; stack[0] = NULL; stack[1] = NULL;

    return 0;

}
