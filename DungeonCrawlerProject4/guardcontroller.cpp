#include "guardcontroller.h"

GuardController::GuardController(long _pattern) :
    pattern(_pattern),
    patternInStr(std::to_string(_pattern))
{

}


int GuardController::move()
{
    char n;

    index == (int)patternInStr.size()-1 ? index = 0 : index++;

    n = patternInStr.at(index)-48;

    switch(n)
    {
    case 1: return 'y'; break;
    case 2: return 's'; break;
    case 3: return 'x'; break;
    case 4: return 'a'; break;
    case 6: return 'd'; break;
    case 7: return 'q'; break;
    case 8: return 'w'; break;
    case 9: return 'e'; break;
    default: return 0;  break;
    }
}



 std::string GuardController::getName() const  {return "Guard Player";}
