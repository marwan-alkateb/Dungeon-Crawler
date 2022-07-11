#include "consolecontroller.h"

ConsoleController::ConsoleController()
{

}



int ConsoleController::move()
{
    return getch();
}



std::string ConsoleController::getName() const  {return "Console Player";}
