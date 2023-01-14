#include "CRoute.h"
#include <iostream>

// ---------------------- \\ 

/*  Time jump cal:
    dist_div = 15m
    vm       = 35 km/h
*/

// ---------------------- \\

#define JUMP_TIME 2  // t_div = (3600s * dist_div) / (vm *1000)

using namespace std;
//=====================================================
//=====================================================
// ***********Beginning of Constructor/Destructor: ****

    CRoute::CRoute(unsigned short int id)
        : r_ID(id) 
    {
        //this->pRoute = new vector<CNode>;
        //this->pMem_route = new vector<vector<CNode>>(0);
    }

    //------------------------------------------------

    CRoute::~CRoute()
    {
        //delete this->pRoute;
        //delete this->pMem_route;
    }

// ***********End of Constructor/Destructor: *********
//====================================================
//====================================================
//**************** Public Funtions *******************
//____________________________________________________

//**************** Gets and Sets *********************
//----------------- Get index Node -------------------

void CRoute::printRouteAndMem(){

    unsigned int len_r  = this->Route.size();
    unsigned int len_mi = this->Mem_route.size();
    
    cout << "_________________________________________________________________________________\n";
    cout << "\t\t\tPrint route begin:\n\n";
    
    for(unsigned short int i = 0 ; i < len_r ; i++ ){
        cout << " (" << this->Route[i].getId() << ") ";
    }

    cout << "\n\nMem_Route: \n";

    for(unsigned short int i = 0 ; i < len_mi ; i++ ){
        unsigned int len_mj = this->Mem_route[i].size();
        for(unsigned short int j = 0 ; j < len_mj ; j++ )
            cout << " (" << this->Mem_route[i][j].getId() << ") ";
        cout << endl;
    }
    cout << "\n\n\t\t\tPrint route end:\n\n";
    cout << "_________________________________________________________________________________\n";
    
}

CNode CRoute::getNode(unsigned short int index)
{
    return this->Route.at(index);
}
//----------------- Get Route ID ---------------------
unsigned short int CRoute::getRouteID()  
{
    return this->r_ID;
}

//----------------- Get Total Gain -------------------
unsigned short int CRoute::getTotalGain()
{
    return this->Route.size();
}

//----------------- Get Route Time -------------------
double CRoute::getRouteTime()
{
    return (double)(this->Route.size() * JUMP_TIME);
}

//-------------- Get Route Position ------------------
SCoord CRoute::getRoutePos(unsigned short int index) 
{
    return this->Route.at(index).getPoint();
}

// ***********End of Public Functions: ***************
//====================================================
//====================================================
