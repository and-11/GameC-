
#include "functions.h"



#include "potion.h"
#include "player.h" 
#include "game.h" 
#include "goblin.h" 
#include "item.h" 
#include "entity.h" 
#include "exception.h" 
#include "functions.h" 
#include "user_interface.h"

void Play_the_game()
{
    Game level,lvl2;
    UI jocc;
    
    std::shared_ptr<Entity> x = std::make_shared<Player>( 110,10000,"KING",2,2 ) ;
    
    level.add_creature( x );
    

    
    std::shared_ptr<Item> y = std::make_shared<Potion>( "Healing",-1,25 );
    level.add_item( y );

    y = std::make_shared<Potion>( "Lightning",0,-100 );
    level.add_item( y );


    y = std::make_shared<Potion>( "Increase_stats",4,4 );
    level.add_item( y );

    // x= std::make_shared<Player>( 1,1000,"Flavius",1,1 );
    // level.add_creature( x );
    // x= std::make_shared<Player>( 2,500,"Maria_t",1,1 );
    // level.add_creature( x );
    
    x= std::make_shared<Goblin>( 2 );
    level.add_creature( x );
    jocc.Add_level(level);
    
    x= std::make_shared<Goblin>( 4 );
    level.add_creature( x );
    jocc.Add_level(level);
    
    // x= std::make_shared<Goblin>( 2 );
    // level.add_creature( x );
    
    jocc.start();



    

    // while( !level.is_over() )
    // {
        
    //         level.player_turn();
    //         level.enemy_turn();

    //         std::cout <<"\n--------\n";
    //         level.show_status();
    //         std::cout <<"--------\n\n";
    // }

    

}


int main()
{
    
    // std::cout << "WELCOME!\npress:\n S -to start\n Q - to quit\n";
    // while( 1 )
    // {
    //     std::string input_string;
    //     std::cin >> input_string;
    //     char option = input_string[0];
    //     option = std::tolower( option );    

    //     try{
    //         if( option == 's' and input_string.size()==1  )
    //         {
                Play_the_game();
    //             break;
    //         } 
    //         else if( option == 'q' and input_string.size()==1 )
    //         {
                // quit
    //             break;
    //         }
    //         else 
    //             throw MyException( "Invalid input!!\n" );
    //     }
    //     catch( MyException &e ){
    //         std::cout << e.what();
    //     }
    // }
}






/// maybe make the color as a static atribute ?

/// clear window 

/// make typical_errors     NANA to low to high

/// break code into pieces


// make entity a virtual void set_Coeficients() =0;
    //             A PUREE VIRTUAL FUNCTIOONNN

// add const at functions and variables