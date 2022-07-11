#include "level.h"
#include "character.h"
#include "tile.h"
#include "floor.h"
#include "wall.h"
#include "portal.h"
#include "door.h"
#include "switch.h"
#include "userinterface.h"
#include <fstream>
#include "node.h"
#include "item.h"
#include "weapon.h"
#include "armor.h"
#include "potion.h"
#include "elixir.h"
#include "lever.h"
#include "trap.h"
#include "Controller.h"
#include "consolecontroller.h"
#include "stationarycontroller.h"
#include "guardcontroller.h"
#include "attackcontroller.h"


Level::Level( UserInterface* m_ui, const std::string& fileName)
    //: width{m_width} , height{m_height}   int m_width, int m_height,
{
    std::ifstream file {fileName};
    if (!file.good())
    {
        throw std::invalid_argument("File Not Found!");
    }

    vector <Node*> nodes;
    vector <Node*> switches;
    vector <Node*> items;           // DON'T FORGET TO CLEAN SPACE
    vector <Node*> levers;

    while (true)
    {
        Node* n = new Node;
        file >> *n;

        nodes.push_back(n);

        if(file.eof())
            break;
    }

    for(const auto &n: nodes)
    {
        Tile* t = nullptr;
        if (n->name == "Floor")
        {
            t = new Floor( m_ui->getFloor(), n->get<int>("col"), n->get<int>("row"));
            tiles[n->get<int>("col")][n->get<int>("row")] = t;
        }

        else if (n->name == "Wall")
        {
            t = new Wall( m_ui->getWall(), n->get<int>("col"), n->get<int>("row"));
            tiles[n->get<int>("col")][n->get<int>("row")] = t;
        }

        else if (n->name == "Portal")
        {
            if(tiles[n->get<int>("destcol")][n->get<int>("destrow")] == nullptr)
            {
                t = new Portal (m_ui->getPortal(),n->get<int>("col"),n->get<int>("row"),nullptr);
                tiles[n->get<int>("col")][n->get<int>("row")] = t;
            } else {
                t = new Portal (m_ui->getPortal(),n->get<int>("col"),n->get<int>("row"),tiles[n->get<int>("destcol")][n->get<int>("destrow")]);
                tiles[n->get<int>("col")][n->get<int>("row")] = t;
                tiles[n->get<int>("destcol")][n->get<int>("destrow")]->setDestination(tiles[n->get<int>("col")][n->get<int>("row")]);
            }
        }

        else if (n->name == "Door")
        {
            t = new Door( m_ui->getDoorOpened(),m_ui->getDoorClosed(), n->get<int>("col"), n->get<int>("row"));
            tiles[n->get<int>("col")][n->get<int>("row")] = t;
        }

        else if (n->name == "Trap")
        {
            t = new Trap( m_ui->getFloor(),m_ui->getTrap(), n->get<int>("col"), n->get<int>("row"));
            tiles[n->get<int>("col")][n->get<int>("row")] = t;
        }

        else if (n->name == "Switch")
        {
            t = new Switch(m_ui->getSwitchOff(),m_ui->getSwitchOn(),n->get<int>("col"),n->get<int>("row"));
            tiles[n->get<int>("col")][n->get<int>("row")] = t;
            switches.emplace_back(n);
        }

        else if (n->name == "Lever")
        {
            t = new Lever(m_ui->getLever(), n->get<int>("col"), n->get<int>("row"));
            tiles[n->get<int>("col")][n->get<int>("row")] = t;
            levers.emplace_back(n);
        }

        //   <<<<<   ATTENTION : TILE MUST BE INITIALIZED BEFORE ITEM   >>>>>>

        else if (n->name == "Item")
        {
            items.push_back(n);
        }


        else if(n->name == "Character")
        {

            Character* c = new Character(n->get<char>("icon"),n->get<int>("stamina"),n->get<int>("strength"));

            if(n->get<std::string>("controller") == "ConsoleController")
            {
                ConsoleController* ctrl1 = new ConsoleController();
                c->setController(ctrl1);
                c->setEnemy(false);
            }
            else if (n->get<std::string>("controller") == "GuardController")
            {
                GuardController* ctrl2 = new GuardController(n->get<long>("pattern"));
                c->setController(ctrl2);
            }
            else if (n->get<std::string>("controller") == "StationaryController")
            {
                StationaryController* ctrl3 = new StationaryController();
                c->setController(ctrl3);
            }
            else if (n->get<std::string>("controller") == "AttackController")
            {
                AttackController* ctrl4 = new AttackController(this,c);
                c->setController(ctrl4);
            }

            placeCharacter(c,n->get<int>("col"),n->get<int>("row"));
            c = nullptr;
        }



        else if(n->name == "Map Information")
        {
            this->width  = n->get<int>("cols");
            this->height = n->get<int>("rows");

            tiles = new Tile**[width];

            for (int i{0}; i<width; i++)
            {
                tiles[i] = new Tile* [height];
                for ( int j=0; j<height; j++)
                    tiles[i][j] = nullptr;
            }
        }
    }



    //Attaching Doors to their Switches
    Active* a;
    for(auto& s : switches)
    {
        a = dynamic_cast<Active*>(tiles[ s->get<int>("col")][ s->get<int>("row")]);
        std::vector<int> cols = s->get<std::vector<int>>("destcols");
        std::vector<int> rows = s->get<std::vector<int>>("destrows");

        Passive* p;
        for(size_t i{0}; i<cols.size(); i++)
        {
            p = dynamic_cast<Passive*>(tiles[cols[i]][rows[i]]);
            a->attach(p);
            p = nullptr;
        }

        a = nullptr;
    }

    //Attaching Doors to their Levers
    for(auto& s : levers)
    {
        a = dynamic_cast<Active*>(tiles[ s->get<int>("col")][ s->get<int>("row")]);
        std::vector<int> cols = s->get<std::vector<int>>("destcols");
        std::vector<int> rows = s->get<std::vector<int>>("destrows");

        Passive* p;
        for(size_t i{0}; i<2; i++)
        {
            p = dynamic_cast<Passive*>(tiles[cols[i]][rows[i]]);
            a->attach(p);
            p = nullptr;
        }
        a = nullptr;
    }

    // Placing Items on floors
    for(auto& node : items)
    {
        if (node->get<std::string>("type") == "Weapon")
        {
            Item* i = new Weapon(node->get<std::string>("name"),node->get<int>("strbonus"));
            tiles[node->get<int>("col")][node->get<int>("row")]->takeItem(i);
        }

        else if (node->get<std::string>("type") == "Armor")
        {
            Item* i = new Armor(node->get<std::string>("name"),node->get<int>("stabonus"));
            tiles[node->get<int>("col")][node->get<int>("row")]->takeItem(i);
        }

        else if(node->get<std::string>("type") == "Potion")
        {
            Item* i = new Potion(node->get<std::string>("name"),node->get<int>("amount"),node->get<int>("hp"));
            tiles[node->get<int>("col")][node->get<int>("row")]->takeItem(i);
        }

        else if (node->get<std::string>("type") == "Elixir")
        {
            Item* i = new Elixir(node->get<std::string>("name"),node->get<int>("amount"),node->get<int>("hp"));
            tiles[node->get<int>("col")][node->get<int>("row")]->takeItem(i);
        }
    }

    for (auto& n : nodes)
        delete n;
}




int Level::getHeight() const
{
    return height;
}



int Level::getWidth() const
{
    return width;
}



std::vector<Character*> Level::getCharactersVector() const
{
    return characters;
}


Level::~Level()
{
    //Attention: character objects on the heap are destroyed in DungeonCrawler Class
    //cleaning up reserved dynamic space on the heap
    for(auto c : characters)
    {
        if(c != nullptr){
            delete c;
        }
    }

    for (int i{0}; i<width; i++)
    {
        for(int j{0}; j<height; j++)
        {
            delete tiles[i][j];
        }
        delete[] tiles[i];
    }

    delete[] tiles;
}



Tile* Level::getTile (int col, int row)
{
    return tiles[col][row];
}



const Tile* Level::getTile (int col, int row) const
{
    return tiles[col][row];
}


//placeCharacter dient dazu einen Character initial auf einem Feld zu setzen
void Level::placeCharacter (Character* c, int col, int row)
{
    if(!tiles[col][row]->hasCharacter()){
        tiles[col][row]->initializeCharacter(c);
        c->setTile(tiles[col][row]);
        characters.emplace_back(c);
    }
}

