#include "dungeoncrawler.h"
#include "tile.h"
#include <signal.h>

DungeonCrawler::DungeonCrawler() :
    ui{new UserInterface},
    currentLevel{ new Level(ui,"/home/stud/Desktop/Do12y-Team9/Prak4/DungeonCrawlerProject4/5-studi.map") }
{
}



DungeonCrawler::~DungeonCrawler()
{
    delete ui;
    delete currentLevel;
}



bool DungeonCrawler::deleteCharacter(int i)
{
    auto itr = currentLevel->characters.begin();
    itr = itr + i;
    delete currentLevel->characters.at(i);
    currentLevel->characters.at(i) = nullptr;
    return true;
}


bool DungeonCrawler::playersAreDead() const
{
    if(friendsAreDead() == true || enemiesAreDead()== true){
        return true;
    }
    return false;
}



bool DungeonCrawler::friendsAreDead() const
{
    for(auto c : currentLevel->characters)
    {
        if ( c!= nullptr)
        {
            if(c->isEnemy()==false && c->isDead() == false)
                return false;
        }
    }
    return true;
}



bool DungeonCrawler::enemiesAreDead() const
{
    for(auto c : currentLevel->characters)
    {
        if ( c!= nullptr)
        {
            if(c->isEnemy()==true && c->isDead() == false)
                return false;
        }
    }
    return true;
}



void DungeonCrawler::play()
{
    int row,col;
    bool quit = false;
    std::string msg {"Starting The Game!"};
    logger.log(logging::Logger::Level::INFO,msg);
    Character* activePlayer = currentLevel->characters.front();
    char key {'n'};
    int index = 0;
    do {
        row = 0;
        col = 0;
        clear();
        refresh();

        ui->drawPlayersAttributes(currentLevel->characters);
        ui->draw(currentLevel);

        key = currentLevel->characters.at(index)->move();


        switch (key){
        case 's': row++;        break;
        case 'w': row--;        break;
        case 'd': col++;        break;
        case 'a': col--;        break;
        case 'x': row++; col++; break;
        case 'y': row++; col--; break;
        case 'e': row--; col++; break;
        case 'q': row--; col--; break;
        case 'm':
            clear();
            refresh();
            ui->drawPlayerMenu();
            ui->draw(currentLevel);
            key = activePlayer->move();
            switch(key){
            case 'o': quit = true;        break;
            case 'i':
                while(true){
                    clear();
                    refresh();
                    ui->drawPlayerInventory(activePlayer);
                    ui->draw(currentLevel);
                    key = activePlayer->move();

                    if(key == 'o')
                    {
                        break;
                    }

                    else
                    {
                        if (key > 0 && key-48 <= activePlayer->getBackpackSize())
                        {
                            activePlayer->dropByIndex(key-48,activePlayer->getTile());
                        }
                    }
                }

                break;

            default: break;
            }
            break;
        case 'o': {
            std::string msg =  "Finishing The Game!";
            logger.log(logging::Logger::Level::INFO,msg);
            quit = true;        break;
        }
        default:
//            std::string msg =  "Wrong Input";
//            logger.log(logging::Logger::Level::WARN,msg);
            break;
        }


        if(row !=0 || col !=0)
        {
            row = currentLevel->characters[index]->getRow() + row;
            col = currentLevel->characters[index]->getColumn() + col;
            currentLevel->characters[index]->getTile()->moveTo(currentLevel->getTile(col,row));
        }


        index == (int)currentLevel->characters.size()-1 ? index = 0 : index++;
        while(currentLevel->characters[index]->isDead()){
            index == (int)currentLevel->characters.size()-1 ? index = 0 : index++;
            if(playersAreDead()){
                quit = true;
                clear(); //refresh();
                ui->gameOver();
                getch();
                break;
            }
        }

    } while(!quit);
}
