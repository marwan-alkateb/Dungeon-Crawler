#ifndef ACTIVE_H
#define ACTIVE_H
#include <vector>
#include <algorithm>
#include "passive.h"



class Active
{
private:
public:
    std::vector <Passive*> passiveObjects;
    virtual void attach (Passive* passive) = 0;
    virtual void detach (Passive* passive) = 0;
    virtual void notify () = 0;
    virtual void activate() = 0;        //ruft die notify() Methode aller verbundenen Passive-Objekte auf

    virtual ~Active(){}
};

#endif // ACTIVE_H
