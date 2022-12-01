#ifndef __CBusStop__
#define __CBusStop__

#include "CPoint.h"
//#include "CBus.h"
#include <vector>
#include <string>


class CBusStop
{
private:
    std::string name;
    const unsigned int ID;
    CPoint bus_stop_pos;
    //vector <CBus> expected_buses;
    
public:
    CBusStop(std::string name, CPoint pos, unsigned int id);
    ~CBusStop();
    unsigned int getID();
    CPoint       getPos();
    std::string  getName(); 
    void updateDisplay();
};

#endif /*__CBusStop__*/