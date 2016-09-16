#include "attack.h"

struct attack_result* attack(struct elepemon* attacker, struct elepemon* defensor)
{
    struct attack_result* attack_info;
    attack_info = malloc(sizeof(struct attack_result));
    attack_info -> attack_id = "plant2";
    attack_info -> defensor = defensor;
    attack_info -> attacker = attacker;
    attack_info -> effect = 0;
    attack_info->damage_done = 130;
    defensor->hp = (defensor->hp) - (attack_info->damage_done);
    return attack_info;
}
