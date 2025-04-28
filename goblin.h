#pragma once

#include "libraryes.h"

#include "entity.h"

class Goblin: public Entity {
    private:
    
    public:
        static void showInformations() {
            std::cout<<"The goblin - we don't know mutch about the goblin. He is a green dude that is low in healt but has high damage! Be careful the Goblin's damage scales well with his level.\n";
        }
        Goblin()
        {
            std::cerr << "You did not set a level for a Goblin!!\n";
        }
        Goblin(int level) : Entity( level, 4 , 5 , "GOBLIN" , 3 , 1)
        {}
    
    };    
