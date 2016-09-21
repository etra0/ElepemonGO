#include <elepemon.h>
#include <ctype.h>


char* translate_type(enum type value)
{
    char types[4][7] = {
                    "Normal",
	                "Water",
	                "Fire",
	                "Plant" };
    char *final_type = strdup(types[value]);
    return final_type;
}

void print_elepemon(const struct elepemon* elepemon)
{
    if (elepemon == NULL) {
        printf("There's no Elepemon!");
        return;
    }
    char *type = translate_type(elepemon->type);
    int i = 0;
    printf("Name: \t %s\n", elepemon->name);
    printf("HP: \t %d\n", elepemon->hp);
    printf("Defense: %d\n", elepemon->defense);
    printf("Type: \t %s\n", type);
    printf("Pointer: %p\n", elepemon->attack.attacks);
    for (i = 0; i < elepemon->attack.attack_count; i++)
        printf("Attack %d: %s\n", i+1, elepemon->attack.attack_ids[i]);

    free(type);
}

void init_elepemon(struct elepemon* elepemon)
{
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
    for (i = 0; i < elepemon->attack.attack_count; i++) {
        free(elepemon->attack.attack_ids[i]);
    }

    free(elepemon->attack.attack_ids);
    free(elepemon->attack.attacks);

    free(elepemon->name);
}

void parse_type(const char *str, enum type *n)
{
    int i;
    char *str_to_parse = strdup(str);
    for (i = 0; i < strlen(str); i++)
        str_to_parse[i] = tolower(str_to_parse[i]);

    if (!strcmp(str_to_parse, "water")) {
        *n = WATER;
    } else if (!strcmp(str_to_parse, "fire")) {
        *n = FIRE;
    } else if (!strcmp(str_to_parse, "plant")) {
        *n = PLANT;
    } else {
        *n = NORMAL;
    }
    free(str_to_parse);
}
