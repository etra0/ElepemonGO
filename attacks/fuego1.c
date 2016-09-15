#include "attack.h"

struct atack_result* attack(struct elepemon* atacante, struct elepemon* defensor)
{
	printf("%s ataco a %s\n", atacante->name, defensor->name);
}