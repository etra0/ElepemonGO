#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inih/ini.h"
#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0


typedef struct
{
    const char *name;
    const char *attacks;
    int hp;
} elepemon;

static int handler(void* user, const char* section, const char* name,
                   const char* value)
{
    elepemon* pconfig = (elepemon*)user;

    pconfig->name = "Bulbasaur";
    if (MATCH("Bulbasaur", "hp")) {
        pconfig->hp = atoi(value);
    } else if (MATCH("Bulbasaur", "attacks")) {
        pconfig->attacks = strdup(value);
    } else {
        return 0;  /* unknown section/name, error */
    }
    return 1;
}

int main(int argc, char* argv[])
{
    elepemon test;

    if (ini_parse("ELEPEMONES", handler, &test) < 0) {
        printf("Can't load 'ELEPEMONES'\n");
        return 1;
    }
    printf("Config loaded from 'test.ini': name =%s, hp=%d, attacks=%s",
        test.name, test.hp, test.attacks);
    return 0;
}
