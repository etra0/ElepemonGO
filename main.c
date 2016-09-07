#include <stdio.h>
#include "elepemon.h"
#include "inih/ini.h"

#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0

static int handler(void* elepemon, const char* section, const char* name,
                   const char* value)
{
    struct elepemon* actual = (struct elepemon*)elepemon;

    actual->name = strdup(section);
    if (MATCH(section, "hp")) {
        actual->hp = atoi(value);
    } else if (MATCH(section, "defense")) {
        actual->defense = atoi(value);
    } else if (MATCH(section,"type")) {
        actual->type = atoi(value);
    } else {
        return 0;  /* unknown section/name, error */
    }
    return 1;
}

int main()
{
    struct elepemon test;

    init_elepemon(&test);

    /* Verify if the file was loaded correctly and it parses inmediatly*/
    if (ini_parse("ELEPEMONES", handler, &test) < 0) {
        printf("Can't load 'ELEPEMONES'\n");
        return 1;
    }

    print_elepemon(&test);
}
