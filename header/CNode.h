#ifndef __CNode__
#define __CNode__

#include <inttypes.h>

class CNode : public CPoint
{
private:
    uint16_t id;
    uint8_t  byte_info;
    uint16_t gain;

public:
    CNode(uint16_t id, uint8_t byte_info, uint16_t gain);
    ~CNode()
    uint8_t      get_nodeInfo();
    void         set_nodeInfo(uint8_t byte_info);
    bool         is_open();
    uint8_t      get_direction();
    void         setGain(unsigned int G);
    unsigned int getGain(); 
}

#endif /*__CNode__*/
