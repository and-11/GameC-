#pragma once

#include "libraryes.h"
#include "enemy.h"

class Goblin: public Enemy {
    private:
    
    public:
        void show_informations() override{
            std::cout<<"The goblin - we don't know mutch about the goblin. He is a green dude that is low in healt but has high damage! Be careful the Goblin's damage scales well with his level.\n";
        }
        Goblin(int level) : Enemy( level, 4 , 5 , "GOBLIN" , 3 , 1) 
        {}
};    
