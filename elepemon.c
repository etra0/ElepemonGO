#include "elepemon.h"

void print_elepemon(const struct elepemon* elepemon)
{
    if (elepemon == NULL) {
        printf("There's no Elepemon!");
        return;
    }
    printf("Name: \t %s\n", elepemon->name);
    printf("HP: \t %d\n", elepemon->hp);
    printf("Defense: %d\n", elepemon->defense);
    printf("Type: \t %d\n", elepemon->type);
}

void init_elepemon(struct elepemon* elepemon)
{
    elepemon = malloc(sizeof(struct elepemon));

    /* First the int types */
    elepemon->hp = 0;
    elepemon->power = 0;
    elepemon->defense = 0;

    elepemon->type = NORMAL;

    elepemon->name = NULL;

    /* Inside the struct attack */
    elepemon->attack.attack_ids = NULL;
    elepemon->attack.attacks = NULL;
    elepemon->attack.attack_count = 0;
}
