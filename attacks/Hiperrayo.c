#include "attack.h"

struct attack_result* attack(struct elepemon* attacker, struct elepemon* defensor)
{
    struct attack_result* attack_info;
    int power, defense, standard_damage;
    attack_info = malloc(sizeof(struct attack_result));
    attack_info->attack_id = "Hiperrayo";
    attack_info->defensor = defensor;
    attack_info->attacker = attacker;
    attack_info->effect = CONFUSED;
    power = attacker->power;
    defense = defensor->defense;
    standard_damage = (power/2)-(defense/3);

    attack_info->effective = NOTVERY;
    attack_info->damage_done = 120+standard_damage;

    defensor->hp = (defensor->hp) - (attack_info->damage_done);
    return attack_info;
}
