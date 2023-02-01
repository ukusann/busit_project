#ifndef __CBusStop__
#define __CBusStop__

#include "CNode.h"
//#include "CBus.h"
#include <vector>
#include <string>


class CBusStop
{
private:
    std::string name;
    const unsigned int ID;
    CNode bus_stop_node;
    //vector <CBus> expected_buses;
    
public:

    CBusStop (std::string name, CNode n, unsigned int id);
    ~CBusStop();
    unsigned int getID();
    SCoord       getPos();
    std::string  getName(); 
    void updateDisplay();
};

#endif /*__CBusStop__*/