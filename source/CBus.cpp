#include "CBus.h"

using namespace std;

//=================Constructor========================
CBus::CBus(uint16_t id, EBus bus_type)
    : BUS_ID(id), bus_type(bus_type)
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

//=================Create Schedule====================
bool CBus::createSchedule()
{
    /*CODE HERE*/
}
//====================================================



