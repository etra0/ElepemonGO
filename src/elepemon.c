#include "../lib/elepemon.h"

void print_elepemon(const struct elepemon* elepemon)
{
    if (elepemon == NULL) {
        printf("There's no Elepemon!");
        return;
    }
    int i = 0;
    printf("Name: \t %s\n", elepemon->name);
    printf("HP: \t %d\n", elepemon->hp);
    printf("Defense: %d\n", elepemon->defense);
    printf("Type: \t %d\n", elepemon->type);
    for(i = 0; i < elepemon->attack.attack_count; i++)
        printf("ATTACK %d: %s\n", i+1, elepemon->attack.attack_ids[i]);

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

void free_elepemon(struct elepemon* elepemon)
{
    int i;
    fprintf(stderr, "%s attackcount: %d\n", elepemon->name, elepemon->attack.attack_count);
    for(i = 0; i < elepemon->attack.attack_count; i++) {
        free(elepemon->attack.attack_ids[i]);
    }
    
    free(elepemon->attack.attack_ids);
    free(elepemon->attack.attacks);

    free(elepemon->name);
}
