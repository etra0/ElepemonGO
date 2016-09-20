#include "../lib/elepemon.h"
#include "../lib/handler_stack.h"

handler_stack *global_handlers = NULL;

char** get_attack_ids(const char* str, int* n)
{
	int i = 0;
	*n = 0;

	char **array;

	char *token, *strcopy;

	strcopy = strdup(str);

	for (i = 0; i < strlen(str); i++)
		if (str[i] == ',')
			(*n)++;
	/* al ser en el formato at1,at2 falta contar un ataque, por ende: */
	(*n)++;

	array = malloc(sizeof(char *) * (*n));
	i = 0;

	while ((token = strsep(&strcopy, ",")) != NULL) {
		*(array+i) = strdup(token);
		i++;
	}

	free(strcopy); free(token);

	return array;
}

void read_attacks(struct elepemon *elepemon)
{
	int quantity = elepemon->attack.attack_count;
	while (quantity--) {
		printf("%s\n", elepemon->attack.attack_ids[quantity]);
	}
}

int load_attacks(const char* attacks_filedir, struct elepemon* elepemon)
{
	int i = 0;

	void *handle;
	char filename[100];

	elepemon->attack.attacks = malloc(sizeof(attack_t) * (elepemon->attack.attack_count));

	for (i = 0; i < elepemon->attack.attack_count; i++) {
		memset(filename, '\0', 100);
		strcat(filename, attacks_filedir);
		if (attacks_filedir[strlen(attacks_filedir)-1] != '/')
			strcat(filename, "/");
		strcat(filename, "lib");
		strcat(filename, elepemon->attack.attack_ids[i]);
		strcat(filename, ".so");

		handle = dlopen(filename, RTLD_NOW);
		dlerror();

		push_handler(&global_handlers, handle);

		*(elepemon->attack.attacks+i) = dlsym(handle, ATTACK_FN);
	}

	return 1;
}

int verify_attack(struct elepemon *elepemon, char *str)
{
	int i;
	for (i = 0; i < elepemon->attack.attack_count; i++)
		if (!strcmp(elepemon->attack.attack_ids[i], str))
			return i;
	return -1;
}

void unload_attacks()
{
	while (global_handlers != NULL) {
		pop_handler(&global_handlers);
	}
}

void check_attack(struct attack_result* attack_info)
{
    printf("%s ha usado %s contra %s\n",attack_info->attacker->name, attack_info->attack_id, attack_info->defensor->name);
    printf("Ha causado un daño de %d puntos de vida\n", attack_info->damage_done);

    if (attack_info->effective == NO) {
        printf("No ha sido efectivo\n");
    } else if (attack_info->effective == NOTVERY) {
        printf("No ha sido muy efectivo\n");
    } else if (attack_info->effective == SUPER) {
        printf("Ha sido super efectivo\n");
    }

    if (attack_info->effect == CONFUSED) {
        printf("%s ha quedado confuso\n", attack_info->defensor->name);
    } else if (attack_info->effect == POISONED) {
        printf("%s ha quedado envenenado\n", attack_info->defensor->name);
    } else if (attack_info->effect == PARALYZED) {
        printf("%s ha quedado paralizado\n", attack_info->defensor->name);
    }

    free(attack_info);
    return;
}
