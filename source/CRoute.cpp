#include "CRoute.h"

#define JUMP_TIME 300  // 300s -> 5 min

using namespace std;

//============ Constructor and Destructor ============

    CRoute::CRoute(unsigned short int id)
    {
        this->r_ID         = id;
    }

    //------------------------------------------------

    CRoute::~CRoute(){
        route.clear();
    }

//====================================================
//====================================================
//**************** Public Funtions *******************
//____________________________________________________

//**************** Gets and Sets *********************
//----------------- Get index Node -------------------
CNode CRoute::getNode(unsigned short int index)
    {return this->route[index];}

//----------------- Get Route ID ---------------------
unsigned short int CRoute::getRouteID()  
    {return this->r_ID;}

//----------------- Get Total Gain -------------------
unsigned short int CRoute::getTotalGain()
    {return this->route.size();}

//----------------- Get Route Time -------------------
double CRoute::getRouteTime()
    {return (double)(this->route.size() * JUMP_TIME);}

//-------------- Get Route Position ------------------
SCoord CRoute::getRoutePos(unsigned short int index) 
    {return this->route[index].getPoint();}
