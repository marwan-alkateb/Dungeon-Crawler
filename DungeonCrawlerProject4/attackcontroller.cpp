#include "attackcontroller.h"

AttackController::AttackController(Level* l, Character* c) : level(l), player(c)
{

}



std::list<Point> AttackController::findPath(std::vector<std::vector<char>>& v, int start_x, int start_y, int end_x, int end_y) {
    map m(v);
    Point s(start_x,start_y), e( end_x, end_y );
    aStarAlgorithm as(m);
    std::list<Point> path;

    if( as.search( s, e, m ) ) {
        // Path Cost Can Be Useful for Logging Purposes or Future Uses
        int pathCost = as.path( path );
    }
    return path;
}



int AttackController::move()
{
    int width {level->getWidth()};
    int height {level->getHeight()};

    bool obstacle;
    std::vector<std::vector<char>> v;
    v.resize(width);
    for(int i{0}; i<width; i++){
        v.at(i).resize(height);
    }

    for(int i{0}; i<width; i++){
        for(int y{0}; y<height; y++){
            obstacle = level->getTile(i,y)->checkIfObstacle();
            obstacle? v[i][y] =  1 : v[i][y] = 0;
        }
    }

    std::list<Point> path;
    int enemyCol= level->getCharactersVector().front()->getColumn();
    int enemyRow = level->getCharactersVector().front()->getRow();
    path = findPath(v,player->getColumn(),player->getRow(),enemyCol,enemyRow);

    auto i = path.begin();  //std::list<Point>::iterator
    i++;
    int x = (*i).x - player->getColumn();
    int y = (*i).y - player->getRow();

    char c;

    switch(x)
    {
    case -1:
        switch(y){
        case -1:    c = 'q';    break;
        case 0:     c = 'a';    break;
        case +1:    c = 'y';    break;
        }
        break;

    case 0:
        switch(y){
        case -1:    c = 'w';    break;
        case 0:     c = '0';    break;
        case +1:    c = 's';    break;
        }
        break;

    case 1:
        switch(y){
        case -1:    c = 'e';    break;
        case 0:     c = 'd';    break;
        case +1:    c = 'x';    break;
        }
        break;
    }

    return c;
}


std::string AttackController::getName() const {return "Attack Player";}


// list iteration
//for( std::list<Point>::iterator i = path.begin(); i != path.end(); i++ ) {
//    std::cout<< "(" << ( *i ).x << ", " << ( *i ).y << ") ";
//}
