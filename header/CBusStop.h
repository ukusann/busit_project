#ifndef __CBusStop__
#define __CBusStop__

#include "CNode.h"
//#include "CBus.h"
#include <vector>
#include <string>


class CBusStop
{
private:
    uint16_t ID;
    CNode bus_stop_node;
    //vector <CBus> expected_buses;
    
public:

    CBusStop (CNode n, uint16_t id);
    ~CBusStop();
    void     setID(uint16_t id);        
    uint16_t getID();
    SCoord   getPos();
    void updateDisplay();
};

#endif /*__CBusStop__*/