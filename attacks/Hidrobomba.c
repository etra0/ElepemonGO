#include "attack.h"

struct attack_result* attack(struct elepemon* attacker, struct elepemon* defensor)
{
    struct attack_result* attack_info;
    int power, defense, standard_damage;
    attack_info = malloc(sizeof(struct attack_result));
    attack_info->attack_id = "Hidrobomba";
    attack_info->defensor = defensor;
    attack_info->attacker = attacker;
    attack_info->effect = PARALYZED;
    power = attacker->power;
    defense = defensor->defense;
    
    if(power>defense){
        standard_damage = (power/2)-(defense/3);
    }else{
        standard_damage = (power/2);
    }
    if (defensor->type == FIRE) {
        attack_info->effective = SUPER;
        attack_info->damage_done = 200+standard_damage;
    } else if (defensor->type == PLANT) {
        attack_info->effective = NO;
        attack_info->damage_done = 0;
    } else {
        attack_info->effective = NONE;
        attack_info->damage_done = standard_damage;
    }

    defensor->hp = (defensor->hp) - (attack_info->damage_done);
    return attack_info;
}
