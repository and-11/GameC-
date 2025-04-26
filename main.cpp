#include <iostream>

#include <vector>
#include <memory>

#include <cctype>

#include <random>
#include <climits>

#include <cstdlib>

void clear_window()
{
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // Unix/Linux/macOS
    #endif
}

int getRandomNumber() {
    
    int low = 1, high = INT_MAX;
    
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(low, high);
    return distr(gen);
}

class MyException : public std::exception
{
private:
	std::string message;

public:
	MyException(const std::string& s) : message{ s } {}

	const char* what() const throw() override {
		return this->message.c_str();
	}
};


class Entity{
private:
protected:
    int level,damage,health,current_health,current_damage;
    int coeficient_damage,coeficient_health;
    std::string name;
    bool player;
public:
    Entity()
    {
        level = damage = health = 0;
        name = "Forgotten";
        player =0;
    }
    Entity(const int level,const int damage,const int health,const std::string name, const int c_damage, const int c_health )
    {
        player =0;
        this->level= level;
        this->damage = damage;
        this->health = health;
        this->name = name;
        this->coeficient_damage = c_damage;
        this->coeficient_health = c_health;
    }
    virtual ~Entity() = default;
    bool is_alive() 
    {
        return current_health > 0;
    }
    friend std::ostream& operator<<(std::ostream& os,const Entity& dude) {
        os << dude.name << " dmg:" << dude.current_damage << " hp:" << dude.current_health ;
        return os;
    }
    void Ready()
    {
        current_damage = damage + coeficient_damage*level;
        current_health = health + coeficient_health*level;
    }
    std::string get_name()
    {
        std::string ans,beg,end="\033[0m";
        if( is_player() )
            beg = "\033[32m";
        else 
            beg = "\033[31m";
        ans = beg+name+end;
        return ans;
    }
    bool is_player()
    {
        return player;
    }
    int get_damage()
    {
        return current_damage;
    }
    std::string show_damage()
    {
        std::string ans,beg,end="dmg\033[0m";
        if( is_player() )
            beg = "\033[32m";
        else 
            beg = "\033[31m";
        ans = beg+std::to_string(current_damage)+end;
        return ans;
    }
    void recive_damage(int value)
    {
        current_health -= value;
    }
    // virtual void set_Coeficients() =0;


    //             A PUREE VIRTUAL FUNCTIOONNN
};

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
class Item{
public:
    virtual void Description() = 0;
};


class Potion: public Item{
// private:    
//     int damage_increase,health_increase;
// public:    
//     void Use( Player & dude )
//     {
//         dude.current_damage += damage_increase;
//         dude.current_health += health_increase;
//     }    
//     Potion() : damage_increase{0} , health_increase{0} 
//     {}
//     Potion(int damage_i,int health_i) : damage_increase{damage_i} , health_increase{health_i} 
//     {}
//     friend std::ostream& operator<<(std::ostream& os,const Potion& pot) {
//         os << pot.damage_increase << "dmg " << pot.health_increase << "hp";
//         return os;
//     }    
    
};    

class Player: public Entity{
private:    
public:
    Player()
    {
        std::cerr << "You did not set stats for a Player!!\n";
    }    
    Player(int damage,int health,std::string name,int c_damage,int c_health) : 
        Entity( 1, damage, health, name , c_damage, c_health )
    {
        player =1;
    }    
    friend Potion;
};    


class Game{
private:
    std::vector< std::shared_ptr<Entity> > entities;
    std::vector< std::shared_ptr<Item> > items;

public:
    void add_creature( std::shared_ptr<Entity> dude )
    {
        entities.push_back( dude );
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
        show_players();
        show_enemies();
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
            std::cout << "\033[1;35m" << "YOU WON!\n" << "\033[0m";
            return 1;
        }
        else if( !count_players() )
        {
            std::cout << "\033[33m" << "YOU LOST!\n" << "\033[0m";
            return 1;
        }
        return 0;
    }
    void player_turn()
    {
        for(auto x:entities)
        {
            if( count_enemies() == 0 )
                break;

            if( x->is_alive() and x->is_player() )    
            {
                std::cout << "Chose an enemy for " << x->get_name() << " to atack:\n";
                show_enemies();
                int n = count_enemies();
                
                while( 1 )
                {
                    
                    int option;
                    std::cin >> option;
                    
                    try{
                        if( 0<option and option<=n )
                        {
                            int ct =0;
                            for(auto y:entities) 
                            if( y->is_alive() and !y->is_player() )
                            {
                                ct++;
                                if( ct == option )
                                {
                                    attack( x,y );
                                    break;
                                }
                            }
                            break;
                        } 
                        else 
                        throw MyException( "Invalid input!!\n" );
                    }
                    catch( MyException &e ){
                        std::cout << e.what();
                    }
                }
            }
            
        }
    }
};



void Play_the_game()
{
    Game level;
    // Entity *x = new Player( 5,10,"Cosmin",2,2 );
    
    std::shared_ptr<Entity> x = std::make_shared<Player>( 500,100,"Aurel",2,2 ) ;
    level.add_creature( x );
    // x= std::make_shared<Player>( 1,3,"Delia",1,1 );
    // level.add_creature( x );
    // x= std::make_shared<Player>( 2,5,"Maria_t",1,1 );
    // level.add_creature( x );


    x= std::make_shared<Goblin>( 2 );
    level.add_creature( x );
    x= std::make_shared<Goblin>( 4 );
    level.add_creature( x );
    x= std::make_shared<Goblin>( 2 );
    level.add_creature( x );


    
    level.prepare_fight();

    std::cout <<"\n--------\n";
    level.show_status();
    std::cout <<"--------\n\n";


    while( !level.is_over() )
    {
        
            level.player_turn();
            level.enemy_turn();

            std::cout <<"\n--------\n";
            level.show_status();
            std::cout <<"--------\n\n";
    }

    

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