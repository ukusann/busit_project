#include "CBus.h"

using namespace std;

//=================Constructor========================
CBus::CBus(uint16_t id, EBus bus_type = EBus::normal_bus)
    : bus_id(id), bus_type(bus_type)
{
    this->pBusStopsList = new vector<CBusStop>(0);
    this->pSchedule     = new vector<SSchedule>(0); 
}
//====================================================

//=================Destructor=========================
CBus::~CBus()
{
    delete pBusStopsList;
    delete pSchedule;
}
//====================================================

//-----------------------------------------------------------
//-----------------------------------------------------------

//***********************************************************
//************Beginning of Private Functions*****************

//=================Next Route=========================
bool CBus::nextRoute()
{
  /*CODE HERE*/  
};
//====================================================

//=================Validate Finish====================
bool CBus::validadeFinish()
{
    /*CODE HERE*/
}
//====================================================

//=================Request Generate Route=============
bool CBus::requestGenerateRoute(CPoint pos_i, CPoint pos_f)
{
    /*CODE HERE*/
}
//====================================================

//=================Answer Pickup======================
bool CBus::answerPickup()
{
    /*CODE HERE*/
}
//====================================================

//=================Create Schedule====================
bool CBus::createSchedule()
{
    /*CODE HERE*/
}
//====================================================

//************End of Private Functions***********************
//***********************************************************

//***********************************************************
//************Beginning of Public Functions******************

//=================Get Schedule====================
vector<SSchedule> CBus::getSchedule()
{
    /*CODE HERE*/
}
//====================================================

//=================Get Route Number===================
uint16_t CBus::getNumRoutes()
{
    /*CODE HERE*/
}
//====================================================

//=================Get Bus ID====================
uint16_t CBus::getBusID()
{
    return this->bus_id;
}
//====================================================

//=================Get Bus Type=======================
EBus CBus::getBusType()
{
    return this->bus_type;
}
//====================================================

//=================Get Bus Arrival Time===============
double CBus::getBusArrivalTime()
{
    /*CODE HERE*/
}
//====================================================

//=================Insert Bus Stop====================
bool CBus::insertBusStop(CBusStop bs)
{
    bool errorFlag = false;
    int bsSize = pBusStopsList->size(); 
    if(bsSize == 0)
        pBusStopsList->push_back(bs);
    else
    {
       for(int i = 0; i < bsSize; i++){
            if(pBusStopsList->at(i).getID() == bs.getID())
            {
                errorFlag = true;
                break;
            }   
       } 
       if(errorFlag)
            return false; 
        else
        {
            pBusStopsList->push_back(bs);
            return true; 
        }
    }
}
//====================================================

//=================Get Bus Type=======================
bool CBus::removeBusStop(CBusStop bs)
{
    bool errorFlag = true;
    int bsSize = pBusStopsList->size(); 
    if(bsSize == 0)
        return false;
    else
    {
       for(int i = 0; i < bsSize; i++){
            if(pBusStopsList->at(i).getID() == bs.getID())
            {
                errorFlag = false;
                pBusStopsList->erase(pBusStopsList->begin() + i);
                break;
            }   
       } 
       if(errorFlag)
            return false; // returns false if an error happens
        else
        {
            return true; // returns true if no errors happens
        }
    }    
}
//====================================================

//=================Clear Bus Stops List=======================
void CBus::clearBusStopsList()
{
    this->pBusStopsList->clear();
}
//====================================================

//=================Set Bus Id=======================
void CBus::setBusId(uint16_t id)
{
    this->bus_id = id;
}
//====================================================
