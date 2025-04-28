#pragma once

#include "libraryes.h"
#include "entity.h"
#include "item.h"
#include "exception.h"

class Game{
    private:
        std::vector< std::shared_ptr<Entity> > entities;
        std::vector< std::shared_ptr<Item> > items;
        bool game_is_lost;
    public:
        Game() : game_is_lost{0}
        {}
        bool is_game_lost()
        {
            return game_is_lost;
        }
        void add_creature( std::shared_ptr<Entity> dude )
        {
            entities.push_back( dude );
        }

        void game_transfer( Game&next_level )
        {
            for( auto x:entities )
                if( x->is_player() )
                    next_level.add_creature( x );
            
            for( auto x:items )                                     /// MAYBE TEST
                next_level.add_item( x );
        }

        void add_item( std::shared_ptr<Item> it )
        {
            items.push_back(it);
        }
        void show_players()
        {
            int ct = 0;
            std::cout << "\033[32m";
            if( count_players() > 0 )
                std::cout << "Heroes\n";
            for(auto x:entities)
            if( x->is_alive() and x->is_player() )
                std::cout << "#" << (++ct) << " " << (*x) << "\n";   
            std::cout << "\033[0m"; /// color
        }
        int count_players()
        {
            int ct = 0;
            for(auto x:entities)
                if( x->is_alive() and x->is_player() )
                    ct++;
            return ct;
        }
        void show_enemies()
        {
            int ct = 0;
            std::cout << "\033[31m"; /// color
            if( count_enemies() > 0 )
                std::cout << "Enemies\n";
            for(auto x:entities)
                if( x->is_alive() and !x->is_player() )
                    std::cout  << "#" << (++ct) << " " << *x << "\n";
            std::cout << "\033[0m"; /// color
        }
        int count_enemies()
        {
            int ct = 0;
            for(auto x:entities)
                if( x->is_alive() and !x->is_player() )
                    ct++;
            return ct;   
        }
        void show_status()
        {
            std::cout <<"--------\n";
            show_players();
            show_enemies();
            std::cout <<"--------\n";
        }
        void show_items()
        {
            int ct = 0 ;
            for(auto x:items)
                std::cout << "\033[36m#" << ++ct << " " << (*x) << "\n";
        }
        void prepare_fight()
        {
            for(auto x:entities)
            {
                x->Ready();
            }
        }
        void attack( std::shared_ptr<Entity> a , std::shared_ptr<Entity> b )  ///     a il ataca pe B!
        {
            b->recive_damage( a->get_damage() );
            std::cout << a->get_name() << " attacked " << b->get_name() << " for " << a->show_damage() << "\n";
        }
        std::shared_ptr<Entity> get_xth_enemy(int ct)
        {
            int og_ct = ct;
            for(auto x:entities)
                if( x->is_alive() and !x->is_player() )
                {
                    ct--;
                    if( !ct )
                        return x;
                }
            std::string msg = "THERE IS NO ENEMY #" + std::to_string(og_ct) ;
            throw MyException( msg );

            std::shared_ptr<Entity> err ;
            return err;
        }
        std::shared_ptr<Entity> get_xth_player(int ct)
        {
            for(auto x:entities)
                if( x->is_alive() and x->is_player() )
                {
                    ct--;
                    if( !ct )
                        return x;
                }
            std::shared_ptr<Entity> err ;
            return err;
        }
        void count_attack(int ct_player,int ct_enemy)
        {
            std::shared_ptr<Entity> pl,en;
            pl = get_xth_player( ct_player );
            en = get_xth_enemy( ct_enemy );
            attack( pl,en );
        }
        void enemy_turn()
        {
            for(auto x:entities)
                if( x->is_alive() and !x->is_player() )    
                {
                    if( count_players() == 0 )
                        break;
    
                    int who = getRandomNumber() % count_players() + 1 ;
                    int ct=0;
                    for(auto y:entities) 
                        if( y->is_alive() and y->is_player() )
                        {
                            ct++;
                            if( ct == who )
                            {
                                attack( x,y );
                                break;
                            }
                        }
                }
        }
        bool is_over()
        {
            if( !count_enemies() )
            {
                std::cout << "\033[1;35m" << "YOU WON THIS LEVEL!\n" << "\033[0m";
                return 1;
            }
            else if( !count_players() )
            {
                game_is_lost = 1;
                std::cout << "\033[33m" << "YOU LOST!\n" << "\033[0m";
                return 1;
            }
            return 0;
        }
        std::string th_player_name(int i)
        {
            try{
                int ct = 0;
                for(auto x:entities)
                if( x->is_alive() and x->is_player() )
                {
                    ct++;
                    if( ct==i )
                    return x->get_name();
                }   
                throw MyException("th_player_name -> THERE ARE NOT ENOUGH PLAYERS");
            }
            catch( MyException& e  )
            {
                return e.what();
            }
        }
        
    };

