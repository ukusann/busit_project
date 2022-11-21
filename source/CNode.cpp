#include "CNode.h"

#define MASK_OPEN  128

//=================Constructor========================
CNode::CNode(uint16_t id, uint8_t byte_info, uint16_t gain = 0, SCoord c = {0,0}): CPoint(c) 
{
    this->id         = id;
    this->byte_info  = byte_info;
    this->gain       = gain;
}
//====================================================

//=================Destructor=========================
CNode::~CNode(){}
//====================================================

//=================Get Node Info======================
uint8_t CNode::get_nodeInfo()
{
    return this->byte_info;
}
//====================================================

//=================Set Node Info======================
void CNode::set_nodeInfo(uint8_t byte_info)
{
    this->byte_info = byte_info;
}
//====================================================

//=================Is open============================
bool CNode::is_open()
{
    bool flag = true;

    if (MASK_OPEN & byte_info == 0)
        flag = false;
    
    return flag;
}
//====================================================

//=================Get Direction======================
uint8_t CNode::get_direction(){
    return 0;
}
//====================================================

//=================Set Gain===========================
void CNode::setGain(uint16_t G)
{
    this->gain = G;
}
//====================================================

//=================Get Gain===========================
uint16_t CNode::getGain()
{
    return this->gain;
}
//====================================================