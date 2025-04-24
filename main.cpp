#include <iostream>

#include <vector>

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

class game{
    std::vector<Entity> entities;
    std::vector<Item> items;


    bool is_over()
    {
        int creatures[2];
        creatures[0] = creatures[1] = 0;

        for(auto x:entities)
        {
            if( x.is_alive() )
            {
                creatures[ x.is_player() ]++;
            }
        }
        if( !creatures[ 0 ] )
        {
            std::cout << "YOU WON!\n";
            return 1;
        }
        else if( !creatures[ 1 ] )
        {
            std::cout << "YOU LOST!\n";
            return 1;
        }
        return 0;
    }
    void add_creature(const Entity& dude )
    {
        entities.push_back(dude);
    }
    void add_item(const Item& it )
    {
        items.push_back(it);
    }
};

int main()
{
    Goblin alex(3);
    // alex.showInformations();
    std::cout << alex << " " << alex;




}