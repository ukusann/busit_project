#ifndef __CNode__
#define __CNode__

#include <inttypes.h>
#include "CPoint.h"


class CNode : public CPoint
{
private:
    uint16_t id;
    uint8_t  byte_info; //byte -> OP | BS | BUS | EN | L | R | U | D
    uint16_t gain;

public:
    CNode(uint16_t id, uint8_t byte_info, uint16_t gain, SCoord c);
    ~CNode();
    uint8_t      get_node_info();
    void         set_node_info(uint8_t byte_info);
    bool         is_open();
    float        get_direction(CPoint &p);
    void         set_gain(uint16_t G);
    uint16_t	 get_gain(); 
};

#endif /*__CNode__*/
