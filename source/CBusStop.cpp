#include "CBusStop.h"


//=================Constructor========================
CBusStop::CBusStop(std::string name, CPoint pos, unsigned int id)
    : name(name), bus_stop_pos(pos), ID(id) {}
//====================================================

//=================Destructor=========================
CBusStop::~CBusStop(){}
//====================================================

//=================Get ID=============================
unsigned int CBusStop::getID()
{
    return this->ID;
}
//====================================================

//=================Get Pos============================
CPoint CBusStop::getPos()
{
    return this->bus_stop_pos;
}
//====================================================

//=================Get Name===========================
std::string CBusStop::getName()
{
    return this->name; 
}
//====================================================
