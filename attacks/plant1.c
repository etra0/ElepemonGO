#include "attack.h"

struct attack_result* attack(struct elepemon* attacker, struct elepemon* defensor)
{
    struct attack_result* attack_info;
    int power, defense, standard_damage;
    attack_info = malloc(sizeof(struct attack_result));
    attack_info -> attack_id = "plant1";
    attack_info -> defensor = defensor;
    attack_info -> attacker = attacker;
    attack_info -> effect = 2;
    power = attacker -> power;
    defense = defensor -> defense;
    standard_damage = (power/2)-(defense/3);

    if(defensor -> type == 0){
        attack_info -> effective = 3;
        attack_info -> damage_done = 60+standard_damage;
    }else if(defensor -> type == 2){
        attack_info -> effective = 0;
        attack_info -> damage_done = 15+standard_damage;
    }else{
        attack_info -> effective = 1;
        attack_info -> damage_done = 50+standard_damage;
    }
    
    defensor->hp = (defensor->hp) - (attack_info->damage_done);
    return attack_info;
}