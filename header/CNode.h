#ifndef __CNode__
#define __CNode__

#include <inttypes.h>
#include "CPoint.h"

#define NODE_OPEN  128
#define NODE_CLOSE 0

class CNode : public CPoint
{
private:
    uint16_t      id;
    unsigned int  byte_info; //byte -> OP | BS | BUS | EN | L | R | U | D
    uint16_t      gain;

public:
    CNode(uint16_t id, unsigned int byte_info, uint16_t x, uint16_t y);
    CNode(uint16_t id, unsigned int byte_info, SCoord s);
    CNode();
    
    ~CNode();
    void            openNode();
    void            closeNode();
    unsigned short int getId();
    unsigned int    getNodeInfo();
    void            setNodeInfo(unsigned int byte_info);
    bool            isOpen();
    float           getDirection(CPoint &p);
    void            setGain(uint16_t G);
    uint16_t	    getGain(); 
    SCoord          getPos(); 
};

#endif /*__CNode__*/
