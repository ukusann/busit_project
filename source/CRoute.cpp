#include "CRoute.h"

#define JUMP_TIME 300  // 300s -> 5 min

using namespace std;
//=====================================================
//=====================================================
// ***********Beginning of Constructor/Destructor: ****

    CRoute::CRoute(unsigned short int id)
        : r_ID(id) 
    {
        this->pRoute = new vector<CNode>;
        this->pMem_route = new vector<vector<CNode>>(0);
    }

    //------------------------------------------------

    CRoute::~CRoute()
    {
        delete this->pRoute;
        delete this->pMem_route;
    }

// ***********End of Constructor/Destructor: *********
//====================================================
//====================================================
//**************** Public Funtions *******************
//____________________________________________________

//**************** Gets and Sets *********************
//----------------- Get index Node -------------------
CNode CRoute::getNode(unsigned short int index)
{
    return this->pRoute->at(index);
}
//----------------- Get Route ID ---------------------
unsigned short int CRoute::getRouteID()  
{
    return this->r_ID;
}

//----------------- Get Total Gain -------------------
unsigned short int CRoute::getTotalGain()
{
    return this->pRoute->size();
}

//----------------- Get Route Time -------------------
double CRoute::getRouteTime()
{
    return (double)(this->pRoute->size() * JUMP_TIME);
}

//-------------- Get Route Position ------------------
SCoord CRoute::getRoutePos(unsigned short int index) 
{
    return this->pRoute->at(index).getPoint();
}

// ***********End of Public Functions: ***************
//====================================================
//====================================================
