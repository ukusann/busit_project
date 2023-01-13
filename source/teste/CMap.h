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

    unsigned short int              len_i;
    unsigned short int              len_j;
    std::vector<std::vector<CNode>> *pmap;
    std::string                     file_name;
    uint8_t                         map_id;
    std::fstream                    file_map;

    bool loadMapFile(std::string file_name);
    bool saveMap();

public:
    CMap(uint8_t map_id);
    ~CMap();
    bool    inputMap(std::string file_name);

    SCoord getMapLen();
    std::vector<std::vector<CNode>> * getPointerMap();
    bool   getMapNode(unsigned short int x, unsigned short int y, CNode *_pmap);

};

#endif /*__CMap__*/
