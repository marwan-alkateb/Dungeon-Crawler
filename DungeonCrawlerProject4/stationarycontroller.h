#ifndef STATIONARYCONTROLLER_H
#define STATIONARYCONTROLLER_H
#include "Controller.h"

class StationaryController : public Controller
{
public:
    StationaryController();
    virtual int move() override;
    std::string getName() const override ;
};

#endif // STATIONARYCONTROLLER_H
