#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <iostream>
using std::string;

class Controller
{
private:
public:
    virtual int move() = 0;
    virtual ~Controller(){};
    virtual std::string getName()const = 0;
};

#endif // CONTROLLER_H
