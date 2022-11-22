#ifndef __CPoint__
#define __CPoint__


struct SCoord{
    unsigned int x;
    unsigned int y;
};

class CPoint
{
private:
    SCoord coord;
    
public:
    CPoint(unsigned int x,unsigned int y);
    CPoint(SCoord c);
    ~CPoint();
    float  getDistance(CPoint &p);
    float  getDistance(SCoord &c);
    SCoord getPoint();
    bool   setPoint(SCoord &c);
    bool   setPoint(CPoint &p);
};

#endif /*__CPoint__*/