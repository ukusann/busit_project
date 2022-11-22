#ifndef __CBusStop__
#define __CBusStop__

#include "CPoint.h"
//#include "CBus.h"
#include <list>
#include <string>


class CBusStop
{
private:
    const unsigned int ID;
    //list <CBus> expected_buses[];
    CPoint bus_stop_pos;
    std::string name;

    void updateDisplay();
public:
    CBusStop(std::string name, CPoint pos, unsigned int id);
    ~CBusStop();
    unsigned int getID();
    CPoint       getPos();
    std::string  getName(); 
};

#endif /*__CBusStop__*/