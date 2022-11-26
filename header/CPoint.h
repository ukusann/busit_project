#ifndef __CPoint__
#define __CPoint__

#include <inttypes.h>


struct SCoord{
    uint16_t x;
    uint16_t y;
};

class CPoint
{
private:
    SCoord coord;
    
public:
    CPoint(uint16_t x, uint16_t y);
    CPoint(SCoord c);
    ~CPoint();
    float       getDistance(CPoint &p);
    float       getDistance(SCoord &c);
    SCoord      getPoint();
    bool        setPoint(SCoord &c);
    bool        setPoint(CPoint &p);
};

#endif /*__CPoint__*/