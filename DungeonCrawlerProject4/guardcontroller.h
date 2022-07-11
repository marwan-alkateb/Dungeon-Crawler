#ifndef GUARDCONTROLLER_H
#define GUARDCONTROLLER_H
#include "Controller.h"
#include <string>

class GuardController : public Controller
{
private:
    long pattern;
    std::string patternInStr;
    int index {-1};
public:
    GuardController(long _pattern);
    virtual int move() override;
    virtual std::string getName() const override;

};

#endif // GUARDCONTROLLER_H
