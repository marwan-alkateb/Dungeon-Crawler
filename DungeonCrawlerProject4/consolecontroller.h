#ifndef CONSOLECONTROLLER_H
#define CONSOLECONTROLLER_H
#include "Controller.h"
#include "ncurses.h"


class ConsoleController : public Controller
{
public:
    ConsoleController();
    virtual int move() override;
    virtual std::string getName() const override;
};

#endif // CONSOLECONTROLLER_H
