#ifndef __CRoute__
#define __CRoute__

#include "CNode.h"
#include <vector>

class CRoute 
{
private:
    std::vector <CNode> route;
    std::vector<std::vector <CNode> > mem_route;
    unsigned short int  r_ID;

public:
    CRoute(unsigned short int id );
    ~CRoute();

    void addNode(CNode n);
    bool insertNode(CNode n, unsigned short int index);
    bool removeNode(unsigned short int index);
    void saveMemoryRoute(std::vector<std::vector<CNode>> mem_r);

    CNode getNode(unsigned short int index);
    unsigned short int getRouteID();
    unsigned short int getTotalGain();
    double             getRouteTime();
    SCoord             getRoutePos(unsigned short int index);
    
    friend class CGenerateRoute;
};

#endif /*__CRoute__*/
