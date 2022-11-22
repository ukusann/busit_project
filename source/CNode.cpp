#include "CNode.h"

#define MASK_OPEN  128

//=================Constructor========================
CNode::CNode(uint16_t id, uint8_t byte_info, uint16_t gain = 0, SCoord c = {0,0})
    : CPoint(c), id(id), byte_info(byte_info), gain(gain)  {}
//====================================================

//=================Destructor=========================
CNode::~CNode(){}
//====================================================

//=================Get Node Info======================
uint8_t CNode::getNodeInfo()
{
    return this->byte_info;
}
//====================================================

//=================Set Node Info======================
void CNode::setNodeInfo(uint8_t byte_info)
{
    this->byte_info = byte_info;
}
//====================================================

//=================Is open============================
bool CNode::isOpen()
{
    bool flag = true;

    if ((MASK_OPEN & byte_info) == 0)
        flag = false;
    
    return flag;
}
//====================================================

//=================Get Direction======================
float CNode::getDirection(CPoint &p){
    return this->getDistance(p); 
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
//====================================================1