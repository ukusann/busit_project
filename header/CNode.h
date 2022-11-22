#ifndef __CNode__
#define __CNode__

#include "CPoint.h"
#include <inttypes.h>


class CNode : public CPoint
{
private:
    uint16_t id;
    uint8_t  byte_info; //byte -> OP | BS | BUS | EN | L | R | U | D
    uint16_t gain;

public:
    CNode(uint16_t id, uint8_t byte_info, uint16_t gain, SCoord c);
    ~CNode();
    uint8_t      getNodeInfo();
    void         setNodeInfo(uint8_t byte_info);
    bool         isOpen();
    float        getDirection(CPoint &p);
    void         setGain(uint16_t G);
    uint16_t	 getGain(); 
};

#endif /*__CNode__*/
