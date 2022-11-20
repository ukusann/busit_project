#include "CNode.h"

//=================Constructor========================
CNode::CNode(uint16_t id, uint8_t byte_info, uint16_t gain = 0)
    : id(id), byte_info(byte_info), gain(gain) {}
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
    /*
        1XXX XXXX

        mask    1000 0000       1000 0000
                NAND            NAND
        byte    1010 1100       0010 1100

        result  0111 1111       1111 1111
                XOR             XOR
        mask    1000 0000       1000 0000

        result  1111 1111       0111 1111
                is open         not open
    */

   //CODE HERE
}
//====================================================

//=================Get Direction======================
uint8_t CNode::get_direction()
{
    //CODE HERE
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