#include "attack.h"

struct attack_result* attack(struct elepemon* attacker, struct elepemon* defensor)
{
    struct attack_result* attack_info;
    int power, defense, standard_damage;
    attack_info = malloc(sizeof(struct attack_result));
    attack_info->attack_id = "fuego1";
    attack_info->defensor = defensor;
    attack_info->attacker = attacker;
    attack_info->effect = NOEFFECT;
    power = attacker->power;
    defense = defensor->defense;
    standard_damage = (power/2)-(defense/3);

    if (defensor->type == PLANT) {
        attack_info->effective = SUPER;
        attack_info->damage_done = 70+standard_damage;
    } else if (defensor->type == WATER) {
        attack_info->effective = NO;
        attack_info->damage_done = 30+standard_damage;
    } else {
        attack_info->effective = NONE;
        attack_info->damage_done = 50+standard_damage;
    }

    defensor->hp = (defensor->hp) - (attack_info->damage_done);
    return attack_info;
}
