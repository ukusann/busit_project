#ifndef __CRoute__
#define __CRoute__

#include "CNode.h"
#include <vector>

class CRoute 
{
private:
    std::vector <CNode> route;
    std::vector<vector <CNode> > mem_route;
    unsigned short int  r_ID;

public:
    CRoute(unsigned short int id );
    ~CRoute();

    CNode getNode(unsigned short int index);
    unsigned short int getRouteID();
    unsigned short int getTotalGain();
    double             getRouteTime();
    SCoord             getRoutePos(unsigned short int index);
    
    friend class CGenerateRoute;
};

#endif /*__CRoute__*/
