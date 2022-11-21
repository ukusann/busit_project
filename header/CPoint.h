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
    float       get_distance(CPoint &p);
    float       get_distance(SCoord &c);
    SCoord      get_point();
    bool        set_point(SCoord &c);
    bool        set_point(CPoint &p);
};

#endif /*__CPoint__*/