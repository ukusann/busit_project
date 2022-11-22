#include "CPoint.h"
#include <cmath>
#include <iostream>


//=================Constructor========================
CPoint::CPoint(unsigned int x, unsigned int y)
{
    coord.x = x;
    coord.y = y;
}

//----------------------------------------------------

CPoint::CPoint(SCoord c)
    : coord(c) {}
//====================================================

//=================Destructor=========================
CPoint::~CPoint(){}
//====================================================

//=================Get Distance=======================
float CPoint::getDistance(CPoint &p)
{
    return sqrt(pow(p.coord.x - this->coord.x, 2) + 
            pow(p.coord.y - this->coord.y, 2));
}

//----------------------------------------------------

float CPoint::getDistance(SCoord &c)
{
    return sqrt(pow(c.x - this->coord.x, 2) +
            pow(c.y - this->coord.y, 2));
}
//====================================================

//=================Get Point==========================
SCoord CPoint::getPoint()
{
    return this->coord;
}
//====================================================

//=================Set Point==========================
bool CPoint::setPoint(SCoord &c)
{
    if(c.x < 0 || c.y < 0)
        return false;
    else
    {
        this->coord.x = c.x;
        this->coord.y = c.y;
        return true;
    }
}

//----------------------------------------------------

bool CPoint::setPoint(CPoint &p)
{
    if(p.coord.x < 0 || p.coord.y < 0)
        return false;
    else
    {
        this->coord.x = p.coord.x;
        this->coord.y = p.coord.y;
        return true;
    }
}
//====================================================
