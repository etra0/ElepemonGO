#include "attack.h"

struct attack_result* attack(struct elepemon* attacker, struct elepemon* defensor)
{
    struct attack_result* attack_info;
    int power, defense, standard_damage;
    attack_info = malloc(sizeof(struct attack_result));
    attack_info->attack_id = "Rapidez";
    attack_info->defensor = defensor;
    attack_info->attacker = attacker;
    attack_info->effect = NOEFFECT;
    power = attacker->power;
    defense = defensor->defense;
    if (power > defense){
        standard_damage = (power/2)-(defense/3);
    } else {
        standard_damage = (power/2);
    }

    attack_info->effective = NO;
    attack_info->damage_done = 100+standard_damage;

    defensor->hp = (defensor->hp) - (attack_info->damage_done);
    return attack_info;
}
