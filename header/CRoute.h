#ifndef __CRoute__
#define __CRoute__

#include "CNode.h"
#include <vector>
#include <string>


class CRoute 
{
private:
    std::vector <CNode> route;
    unsigned short int  r_ID;
    unsigned short int  r_total_gain;
    double              r_total_time;

public:
    unsigned short int getRouteID();
    unsigned short int getTotalGain();
    double             getRouteTime();
    SCoord             getRoutePos(unsigned short int index);
};

#endif /*__CRoute__*/
