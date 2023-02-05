#include "CBusStop.h"
#include <iostream>

using namespace std;
//=================Constructor========================
CBusStop::CBusStop(CNode n, uint16_t id)
    :bus_stop_node(n), ID(id) {

    }
//====================================================

//=================Destructor=========================
CBusStop::~CBusStop(){}
//====================================================

//=================Set ID=============================
void CBusStop::setID(uint16_t id)
{
    this->ID = id;
}
//====================================================

//=================Get ID=============================
uint16_t CBusStop::getID()
{
    return this->ID;
}
//====================================================

//=================Get Pos============================
SCoord CBusStop::getPos()
{
    return this->bus_stop_node.getPos();
}
//====================================================

//=================Update Display=====================
void CBusStop::updateDisplay()
{
    /**/
    std::cout << "CBusStop Info:\n" 
            << "ID: "   << this->ID << endl;  
}
//====================================================