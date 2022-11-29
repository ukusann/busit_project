#ifndef __CBus__
#define __CBus__

#include "CBusStop.h"
#include <list>
#include <inttypes.h>
#include <string>

enum class EBus {normal_bus = 0, small_bus = 1};

struct STime
{
    STime time;
    std::string busStopName;
};

struct SSchedule
{
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
};

class CBus
{
private:
    const uint16_t BUS_ID;
    EBus bus_type;
    //list <CRoute> bus_routes; 
    list<CBusStop> busStopsList;
    list<SSchedule> schedule;

    bool nextRoute();
    bool validadeFinish();
    bool requestGenerateRoute(CPoint pos_i, CPoint pos_f);
    bool answerPickup();
    bool createSchedule();
public:
    list<SSchedule> getSchedule();
    uint16_t getNumRoutes();
    uint16_t getBusID();
    EBus     getBusType();
    double   getBusTimeArrival();
    bool     insertBusStop(CBusStop);     
    bool     removeBusStop(CBusStop);
    //bool     setRoutes(list<CRoute> route);
};

#endif /*__CBus__*/