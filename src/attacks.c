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
	/* al ser en el formato at1,at2 falta contar una coma, por ende: */
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

int load_attacks(const char* attacks_filedir, struct elepemon* elepemon)
{
	int i = 0;

	void *handle;
	char* filename = "";

	elepemon->attack.attacks = malloc(sizeof(attack_t*) * elepemon->attack.attack_count);

	for (i = 0; i < elepemon->attack.attack_count; i++) {
		filename = strdup(attacks_filedir);
		filename = strcat(filename, "/lib");
		filename = strcat(filename, elepemon->attack.attack_ids[i]);
		filename = strcat(filename, ".so");

		handle = dlopen(filename, RTLD_NOW);

		push_handler(&global_handlers, handle);

		elepemon->attack.attacks[i] = dlsym(handle, ATTACK_FN);
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
	while(global_handlers != NULL) {
		dlclose(pop_handler(&global_handlers));		
	}
}