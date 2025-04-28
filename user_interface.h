#pragma once

#include "libraryes.h"
#include "game.h"

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
            int n = current_level->count_enemies();
            
            while( 1 )
            {
                try{
                    int option;
                    std::cin >> option;

                    if (std::cin.fail()) {
                        std::cin.clear(); 
                        std::cin.ignore(10000, '\n'); // discard invalid input
                        throw MyException("Invalid input!!\n");
                    }                                             //// daca coteste litere da fail si nu mai colaboreaza
                                                
                    current_level->count_attack(i,option);
                    break;   
                }  
                catch( MyException &e ){
                    std::cout << e.what() << "\n";
                }
            }
        }
    }
    void chose_action( Game *current_level )
    {
        attack(current_level);

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