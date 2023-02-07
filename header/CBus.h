#ifndef __CBus__
#define __CBus__

#include "CBusStop.h"
#include <vector>
#include <inttypes.h>
#include <string>

enum class EBus {normal_bus = 0, small_bus = 1};

struct STime
{
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
};

struct SSchedule
{
    STime time;
    std::string busStopName;
};

class CBus
{
private:
    uint16_t bus_id;
    EBus bus_type;
    //vector<CRoute> bus_routes; 
    std::vector<CBusStop> BusStopsList;
    std::vector<SSchedule> Schedule;

    //bool nextRoute();
    //bool validadeFinish();
    //bool requestGenerateRoute(CPoint pos_i, CPoint pos_f);
    //bool answerPickup();
    //bool createSchedule();
public:
    CBus(uint16_t id, EBus bus_type);
    ~CBus();
    //std::vector<SSchedule> getSchedule();
    //uint16_t getNumRoutes();
    uint16_t getBusID();
    EBus     getBusType();
    //double   getBusArrivalTime();
    bool     insertBusStop(CBusStop);     
    bool     removeBusStop(CBusStop);
    void     clearBusStopsList();
    void     setBusId(uint16_t id);
    //bool     setRoutes(vector<CRoute> route);
};

#endif /*__CBus__*/