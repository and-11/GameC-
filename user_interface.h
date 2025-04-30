#pragma once

#include "libraryes.h"
#include "game.h"
#include "functions.h"
#include "exception.h"

class UI{
private:
    std::vector<Game> levels;   /// only the first level will contain the players,first


public:
    void Quit(){return;}
    void Add_level(Game x)
    {
        levels.push_back( x );
    }
    void attack( Game *current_level  )
    {
        for(int i=1;i<=current_level->count_players();i++ )
        {
            
            if( !current_level->count_enemies() )
                break;

            std::cout << "\nChose an enemy for " << current_level->th_player_name( i ) << " to atack:\n";

            current_level->show_enemies();
            
            while( 1 )
            {
                try{
                    int option = get_numeric_input();
                                                
                    current_level->count_attack(i,option);
                    break;   
                }  
                catch( MyException &e ){
                    std::cout << e.what() << "\n";
                }
              
            }
        }
    }
    
    bool chose_item( Game *current_level )
    {
        current_level->show_items();
        std::cout << "Chose an item or press 0 to cancel:\n";

        std::shared_ptr<Item> current_item;
        while( 1 )
        {
            try{
                int option = get_numeric_input();
                if( option == 0 )                
                {
                    std::cout << "\nPress 1 to attack or press 2 to use an item:\n";
                    return 0;
                }
                else
                {
                    current_item = current_level->get_xth_item(option);
                    break;
                }
                
            }
            catch( MyException&e )
            {
                std::cout << e.what() << "\n";
            }
        }

        std::cout <<  current_item->get_name() << ": Press 1 to use on a PLAYER and 2 to use on an ENEMY:\n";
        while( 1 )
        {
            try{
                int option = get_numeric_input();   
                if( option == 1 )                
                {
                    std::cout << "\nChose a Hero to use " << current_item->get_name() << " on:\n";
                    current_level->show_players();
                    
                    while( 1 )
                    {
                        try{
                            int option = get_numeric_input();
                            
                            current_level->count_item_use_player( current_item ,option);
                            break;   
                        }  
                        catch( MyException &e ){
                            std::cout << e.what() << "\n";
                        }
                    }  
                    
                    break;
                }
                if( option == 2 )
                {
                    std::cout << "\nChose an enemy  to use " << current_item->get_name() << " on:\n";
                    current_level->show_enemies();
                    
                    while( 1 )
                    {
                        try{
                            int option = get_numeric_input();
                                                        
                            current_level->count_item_use_enemy( current_item ,option);
                            break;   
                        }  
                        catch( MyException &e ){
                            std::cout << e.what() << "\n";
                        }
                    }                    
                    break;
                }
                throw Input_Invalid();              
            }
            catch( MyException&e )
            {
                std::cout << e.what() << "\n";
            }
        }
        

        return 1;
    }
    void chose_action( Game *current_level )
    {
        std::cout << "\nPress 1 to attack or press 2 to use an item:\n";
        while( 1 )
        {
            try{
                int option = get_numeric_input();
                
                if( option == 1 )                
                {
                    attack(current_level);
                    break;
                }
                else if( option == 2 )
                {
                    if( chose_item( current_level ) )
                        break;
                    else 
                        continue;
                }
                throw Input_Invalid();
            }
            catch( MyException&e )
            {
                std::cout << e.what() << "\n";
            }
        }
    }
    void start()
    {
        bool lose = 0;
        for(int i=0;i<levels.size();i++)
        {
            Game *current_level = &levels[i];
            current_level->prepare_fight();

            while( !current_level->is_over() )
            {
                current_level->show_status();
                chose_action( current_level );
                current_level->enemy_turn();
            }
            if( current_level->is_game_lost() )
            {
                lose = 1;
                break;
            }
            else if( i<levels.size()-1 )
            {
                std::cout << "\nLoading next level...\n\n";
                current_level->game_transfer( levels[i+1] );
            }
        }
        if( !lose )
            std::cout << "\033[32m\nCONGRATULATIONS\nYOU WON THE GAME!!!\033[0m\n\n\n";
    }

};


/// replace all the try catches with pointers to functions?     while(1)