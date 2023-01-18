#ifndef __CRoute__
#define __CRoute__

#include "CNode.h"
#include <vector>

class CRoute 
{
private:
    std::vector <CNode> Route;
    std::vector<std::vector <CNode> > Mem_route;
    unsigned short int  r_id;

public:

    CRoute(unsigned short int id);
    CRoute();
    ~CRoute();

    void printRouteAndMem();
    CNode getNode(unsigned short int index);
    unsigned short int getRouteID();
    unsigned short int getTotalGain();
    double             getRouteTime();
    SCoord             getRoutePos(unsigned short int index);
    
    friend class CGenerateRoute;
};

#endif /*__CRoute__*/
