#ifndef __CMap__
#define __CMap__

#include <inttypes.h>
#include <list>
#include "CNode.h"
#include <string>
#include <fstream>

using namespace std;

class CMap 
{
private:

    unsigned int        len_i;
    unsigned int        len_j;
    list<list<CNode>>   map;
    string              file_name;
    uint8_t             map_id;


    bool get_map_init_file(string file_name);
    bool save_map();

public:
    CMap(uint8_t map_id);
    ~CMap();
    bool input_map(string file_name);     
};

#endif /*__CMap__*/
