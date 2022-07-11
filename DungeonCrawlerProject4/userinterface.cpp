#include "userinterface.h"
#include "level.h"
#include "tile.h"
#include <signal.h>
//#include <iomanip>
#include "character.h"


UserInterface::UserInterface()
{
    initscr();
    signal (SIGWINCH,NULL);          //to avoid raising the signal und exiting the program
    noecho();
    curs_set(0);
    cbreak();
}



char UserInterface::getCharacter() const
{
    return character;
}


char UserInterface::getWall() const
{
    return wall;
}


char UserInterface::getFloor() const
{
    return floor;
}


char UserInterface::getPortal() const
{
    return portal;
}


char UserInterface::getSwitchOn() const
{
    return switch_on;
}


char UserInterface::getSwitchOff() const
{
    return switch_off;
}


char UserInterface::getDoorOpened() const
{
    return door_opened;
}


char UserInterface::getDoorClosed() const
{
    return door_closed;
}


char UserInterface::getLever() const
{
    return lever;
}


char  UserInterface::getTrap() const
{
    return trap;
}


UserInterface::~UserInterface()
{
    endwin();
}


void UserInterface::drawPlayerAttributes (Character* activeCharacter)
{

    std::string str {"Active Player "} ;
    str+=activeCharacter->getIcon();
    mvaddstr(1,menuColumn,str.c_str());

    mvaddstr(3,menuColumn,"Status       ");
    str = "Strength:    ";
    str += std::to_string(activeCharacter->getStrength());
    mvaddstr(4,menuColumn,str.c_str());
    str = "Stamina:     ";
    str += std::to_string(activeCharacter->getStamina());
    mvaddstr(5,menuColumn,str.c_str());
    str = "Hit Points:  ";
    str += std::to_string(activeCharacter->getHitPoints());
    mvaddstr(6,menuColumn,str.c_str());
}


void UserInterface::drawPlayersAttributes (std::vector<Character*>& v)
{
    for(size_t i=0; i<v.size(); i+=2)
    {
        std::string str {v[i]->getName()};
        //str+=v[i]->getIcon();
        mvaddstr(1,menuColumn+(i*10),str.c_str());

        mvaddstr(3,menuColumn+(i*10),"Status       ");
        str = "Strength:    ";
        str += std::to_string(v[i]->getStrength());
        mvaddstr(4,menuColumn+(i*10),str.c_str());
        str = "Stamina:     ";
        str += std::to_string(v[i]->getStamina());
        mvaddstr(5,menuColumn+(i*10),str.c_str());
        str = "Hit Points:  ";
        str += std::to_string(v[i]->getHitPoints());
        mvaddstr(6,menuColumn+(i*10),str.c_str());
        str = "Dead:  ";
        str += std::to_string(v[i]->isDead());
        mvaddstr(7,menuColumn+(i*10),str.c_str());
    }

    for(size_t i=1; i<v.size(); i+=2)
    {
        std::string str {v[i]->getName()} ;
        //str+=v[i]->getIcon();
        mvaddstr(1+(10),menuColumn+(i*10-10),str.c_str());

        mvaddstr(3+(10),menuColumn+(i*10-10),"Status       ");
        str = "Strength:    ";
        str += std::to_string(v[i]->getStrength());
        mvaddstr(4+(10),menuColumn+(i*10-10),str.c_str());
        str = "Stamina:     ";
        str += std::to_string(v[i]->getStamina());
        mvaddstr(5+(10),menuColumn+(i*10-10),str.c_str());
        str = "Hit Points:  ";
        str += std::to_string(v[i]->getHitPoints());
        mvaddstr(6+(10),menuColumn+(i*10-10),str.c_str());
        str = "Dead:  ";
        str += std::to_string(v[i]->isDead());
        mvaddstr(7+(10),menuColumn+(i*10-10),str.c_str());
    }
}


void UserInterface::gameOver()
{
    std::string str {"GAME OVER"} ;
    start_color();
    init_pair(3,3,0);
    attron(COLOR_PAIR(3));
    attron(A_BOLD);
    mvaddstr(5,menuColumn+5,str.c_str());
    attroff(A_BOLD);
    attroff(COLOR_PAIR(3));
}


void UserInterface::drawPlayerMenu ()
{
    std::string str {"Player Menu "} ;
    mvaddstr(1,menuColumn,str.c_str());
    mvaddstr(3,menuColumn,"o: Quit Game");
    mvaddstr(4,menuColumn,"i: Show Inventory");
}


void UserInterface::drawPlayerInventory (Character* activeCharacter)
{
    std::string str;
    int num=0;
    if (activeCharacter->getBackpackSize() == 0)
    {
        mvaddstr(1,menuColumn,"Inventory is in the moment empty");
        mvaddstr(2,menuColumn,"Available Options: Press 'o' to return");
    }
    else
    {
        for(auto& n : activeCharacter->getBackpackContent())
        {
            num++;
            str = std::to_string(num) + ". ";
            str += n.c_str();
            mvaddstr(num+1,menuColumn,str.c_str());
        }
    }
}


// Das übergebene Level auf dem Terminal ausgeben
void UserInterface::draw (Level* level)
{

    char c;

    for(int i=0; i<level->getWidth(); i++)
    {
        for (int j=level->getHeight()-1; j>-1; j--)
        {
            c = level->getTile(i,j)->getIcon();
            std::string str (1,c);
            switch(c){
            case character:
                start_color();
                init_pair(3,3,0);
                attron(COLOR_PAIR(3));
                attron(A_BOLD);
                mvaddstr(j+boardColumn,i+boardRow,str.c_str());
                attroff(A_BOLD);
                attroff(COLOR_PAIR(3));
                break;


            case portal:
                start_color();
                init_pair(2,2,0);
                attron(COLOR_PAIR(2));
                attron(A_BOLD);
                mvaddstr(j+boardColumn,i+boardRow,str.c_str());
                attroff(A_BOLD);
                attroff(COLOR_PAIR(1));
                break;

            case door_closed:
                start_color();
                init_pair(1,1,0);
                attron(COLOR_PAIR(1));
                attron(A_BOLD);
                mvaddstr(j+boardColumn,i+boardRow,str.c_str());
                attroff(A_BOLD);
                attroff(COLOR_PAIR(1));
                break;

            case door_opened:
                start_color();
                init_pair(4,4,0);
                attron(COLOR_PAIR(4));
                attron(A_BOLD);
                mvaddstr(j+boardColumn,i+boardRow,str.c_str());
                attroff(A_BOLD);
                attroff(COLOR_PAIR(1));
                break;

            case wall:
                start_color();
                init_pair(5,5,0);
                attron(COLOR_PAIR(5));
                attron(A_BOLD);
                mvaddstr(j+boardColumn,i+boardRow,str.c_str());
                attroff(A_BOLD);
                attroff(COLOR_PAIR(5));
                break;

            default:
                mvaddstr(j+boardColumn,i+boardRow,str.c_str());
                break;
            }
        }
    }
}

