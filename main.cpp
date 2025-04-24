#include <iostream>

#include <vector>
#include <memory>

#include <random>
#include <climits>
int getRandomNumber() {
    
    int low = 1, high = INT_MAX;
    
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(low, high);
    return distr(gen);
}


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
        os << "[ " << dude.name << " dmg:" << dude.current_damage << " hp:" << dude.current_health <<" ]";
        return os;
    }
    void Ready()
    {
        current_damage = damage + coeficient_damage*level;
        current_health = health + coeficient_health*level;
    }
    std::string get_name()
    {
        return name;
    }
    bool is_player()
    {
        return player;
    }
    int get_damage()
    {
        return current_damage;
    }
    void recive_damage(int value)
    {
        current_health -= value;
    }
    // virtual void set_Coeficients() =0;


    ///             A PUREE VIRTUAL FUNCTIOONNN
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
};

class Item{

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
        std::cout << "Heroes\n";
        for(auto x:entities)
        if( x->is_alive() and x->is_player() )
                std::cout << "#" << (++ct) << " " << (*x) << "\n";   
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
        std::cout << "Enemies\n";
        for(auto x:entities)
            if( x->is_alive() and !x->is_player() )
                std::cout  << "#" << (++ct) << *x << "\n";
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
    }
    void enemy_turn()
    {
        for(auto x:entities)
            if( x->is_alive() and !x->is_player() )    
            {
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
            std::cout << "YOU WON!\n";
            return 1;
        }
        else if( !count_players() )
        {
            std::cout << "YOU LOST!\n";
            return 1;
        }
        return 0;
    }

};

int main()
{
    Game level;
    // Entity *x = new Player( 5,10,"Cosmin",2,2 );
    
    std::shared_ptr<Entity> x = std::make_shared<Player>( 5,100,"Cosmin",2,2 ) ;
    level.add_creature( x );
    x= std::make_shared<Player>( 1,40,"Victor",1,1 );
    level.add_creature( x );
    x= std::make_shared<Player>( 2,70,"Pictor",1,1 );
    level.add_creature( x );


    x= std::make_shared<Goblin>( 1 );
    level.add_creature( x );
    // x= std::make_shared<Goblin>( 4 );
    // level.add_creature( x );
    // x= std::make_shared<Goblin>( 2 );
    // level.add_creature( x );


    level.prepare_fight();

    level.show_status();

    std::cout <<"\n";
    level.enemy_turn();
    std::cout <<"\n";
    level.show_status();
    

}