#include "CNode.h"

#define MASK_CLOSE  0x80

//=================Constructor========================
CNode::CNode(uint16_t id, unsigned int byte_info, uint16_t x, uint16_t y)
    : CPoint(x,y), id(id), byte_info(byte_info)  {
        this->gain = 0;
    }

//----------------------------------------------------
    
CNode::CNode(uint16_t id, unsigned int byte_info, SCoord s)
: CPoint(s), id(id), byte_info(byte_info)  {
    this->gain = 0;
}
//----------------------------------------------------

CNode::CNode(): CPoint(0,0), id(0), byte_info(0)
{
    this->gain = 0;
}

//====================================================

//=================Destructor=========================
CNode::~CNode(){}
//====================================================


//====================================================
//====================================================
//**************** Public Funtions *******************
//____________________________________________________
//------------------ Open Node -----------------------
void CNode::openNode(){
    byte_info &= ~MASK_CLOSE;     // 128 0000 0000
}
//____________________________________________________
//------------------ Close Node-----------------------
void CNode::closeNode(){
    byte_info |= MASK_CLOSE;     // 128 1000 0000
}
//____________________________________________________
//----------------- Is open --------------------------
bool CNode::isOpen()
{
    bool flag = true;

    if ((MASK_CLOSE & byte_info) == MASK_CLOSE)
        flag = false;
    
    return flag;
}
//====================================================

//**************** Gets and Sets *********************

//--------------------- Get ID -----------------------
unsigned short int CNode::getId(){
    return this->id;
}

//---------------- Get Node Info ---------------------
unsigned int CNode::getNodeInfo()
    {return this->byte_info;}

//---------------- Get Direction ---------------------
float CNode::getDirection(CPoint &p)
    {return this->getDistance(p);}

//---------------- Get Gain --------------------------
uint16_t CNode::getGain()
    {return this->gain;}

//----------------- Get Point ------------------------
SCoord CNode::getPos()
    {return this->getPoint();}


//----------------- Set Gain -------------------------
void CNode::setGain(uint16_t G)
    {this->gain = G;}

//---------------- Set Node Info ---------------------
void CNode::setNodeInfo(unsigned int byte_info)
    {this->byte_info = byte_info;}