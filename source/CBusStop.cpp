#include "CBusStop.h"
#include <iostream>

using namespace std;
//=================Constructor========================
CBusStop::CBusStop(std::string name, CNode n, unsigned int id)
    : name(name), bus_stop_node(n), ID(id) {

    }
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
SCoord CBusStop::getPos()
{
    return this->bus_stop_node.getPos();
}
//====================================================

//=================Get Name===========================
std::string CBusStop::getName()
{
    return this->name; 
}
//====================================================

//=================Update Display=====================
void CBusStop::updateDisplay()
{
    /**/
    std::cout << "CBusStop Info:\n" 
            << "ID: "   << this->ID << endl
            << "Name: " << this->name << endl;  
}
//====================================================