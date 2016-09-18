#include "attack.h"

struct attack_result* attack(struct elepemon* attacker, struct elepemon* defensor)
{
    struct attack_result* attack_info;
    int power, defense, standard_damage;
    attack_info = malloc(sizeof(struct attack_result));
    attack_info->attack_id = "water1";
    attack_info->defensor = defensor;
    attack_info->attacker = attacker;
    attack_info->effect = 1;
    power = attacker->power;
    defense = defensor->defense;
    
    if (power > defense){
        standard_damage = (power/2)-(defense/3);
    }else{
        standard_damage = (power/2);
    }

    if (defensor->type == 2) {
        attack_info->effective = 3;
        attack_info->damage_done = 90+standard_damage;
    } else if (defensor->type == 3) {
        attack_info->effective = 0;
        attack_info->damage_done = 30+standard_damage;
    } else {
        attack_info->effective = 1;
        attack_info->damage_done = 70+standard_damage;
    }

    defensor->hp = (defensor->hp) - (attack_info->damage_done);
    return attack_info;
}
