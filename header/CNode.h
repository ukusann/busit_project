#ifndef __CNode__
#define __CNode__

#include <inttypes.h>
#include "CPoint.h"


class CNode : public CPoint
{
private:
    uint16_t      id;
    unsigned int  byte_info; //byte -> OP | BS | BUS | EN | L | R | U | D
    uint16_t      gain;

public:
    CNode(uint16_t id, unsigned int byte_info, uint16_t x, uint16_t y);
    ~CNode();
    unsigned int    getNodeInfo();
    void            setNodeInfo(unsigned int byte_info);
    bool            isOpen();
    float           getDirection(CPoint &p);
    void            setGain(uint16_t G);
    uint16_t	    getGain(); 
};

#endif /*__CNode__*/
