#ifndef __CMap__
#define __CMap__

#include <inttypes.h>
#include <list>
#include "CNode.h"
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class CMap 
{
private:

    uint16_t            len_i;
    uint16_t            len_j;
    vector<vector<CNode>>   map;
    string              file_name;
    uint8_t             map_id;
    fstream             file_map;

    bool loadMapFile(string file_name);
    bool saveMap();

public:
    CMap(uint8_t map_id);
    ~CMap();
    bool    inputMap(string file_name);

};

#endif /*__CMap__*/
