#pragma once

#include "libraryes.h"
#include "item.h"
#include "entity.h"


class Potion: public Item{
private:    
    int damage_increase,health_increase;
public:    
    void Use( Entity & dude )
    {
        dude.current_damage += damage_increase;
        dude.current_health += health_increase;
    }    
    Potion() : damage_increase{0} , health_increase{0} 
    {}
    Potion(int damage_i,int health_i) : damage_increase{damage_i} , health_increase{health_i} 
    {}
    void Description()
    {
        std::cout << "A potion is an item that can be used on anny creature, either Hero or Enemy. Be careful how you use them...\n";
    }
    friend std::ostream& operator<<(std::ostream& os,const Potion& pot) {
        os << pot.damage_increase << "dmg " << pot.health_increase << "hp";
        return os;
    }    
        
};   