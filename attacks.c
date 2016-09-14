#include "elepemon.h"

char** get_attack_ids(const char* str, int* n) {
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