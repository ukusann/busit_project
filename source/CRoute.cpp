#include "CRoute.h"

using namespace std;

//**************** Gets and Sets *********************
//----------------- Get Route ID ---------------------
unsigned short int CRoute::getRouteID()  
    {return this->r_ID;}

//----------------- Get Total Gain -------------------
unsigned short int CRoute::getTotalGain()
    {return this->r_total_gain;}

//----------------- Get Route Time -------------------
double CRoute::getRouteTime()
    {return this->r_total_time;}

//-------------- Get Route Position ------------------
SCoord CRoute::getRoutePos(unsigned short int index) 
    {return this->route[index].getPoint();}
