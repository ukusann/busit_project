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
uint8_t CNode::get_node_info()
{
    return this->byte_info;
}
//====================================================

//=================Set Node Info======================
void CNode::set_node_info(uint8_t byte_info)
{
    this->byte_info = byte_info;
}
//====================================================

//=================Is open============================
bool CNode::is_open()
{
    bool flag = true;

    if ((MASK_OPEN & byte_info) == 0)
        flag = false;
    
    return flag;
}
//====================================================

//=================Get Direction======================
float CNode::get_direction(CPoint &p){
    return this->get_distance(p); 
}
//====================================================

//=================Set Gain===========================
void CNode::set_gain(uint16_t G)
{
    this->gain = G;
}
//====================================================

//=================Get Gain===========================
uint16_t CNode::get_gain()
{
    return this->gain;
}
//====================================================