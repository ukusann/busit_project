#ifndef __CMap__
#define __CMap__

#include <inttypes.h>
#include "CNode.h"
#include <vector>
#include <string>
#include <fstream>

class CMap 
{
private:


    uint16_t                        len_i;
    uint16_t                        len_j;
    std::vector<std::vector<CNode>> *pmap;
    std::string                     file_name;
    uint8_t                         map_id;
    std::fstream                    file_map;

    uint16_t                    len_i;
    uint16_t                    len_j;
    std::vector< std::vector <CNode> >  *pmap;
    std::string                 file_name;
    uint8_t                     map_id;
    std::fstream                file_map;

    bool loadMapFile(std::string file_name);
    bool saveMap();

public:
    CMap(uint8_t map_id);
    ~CMap();
    bool    inputMap(std::string file_name);

};

#endif /*__CMap__*/
