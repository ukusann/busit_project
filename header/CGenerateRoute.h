#ifndef __CGenerateRoute__
#define __CGenerateRoute__

#include "CRoute.h"
#include "CMap.h"
#include "CNode.h"
#include <vector>

class CGenerateRoute 
{
private:
    CRoute single_route;
    std::vector<CRoute> multi_route;
    CMap *map_info;

    bool make_route( CNode i_node, CNode f_node,
                     bool opt, unsigned short int max_g);
    CNode decisionMaker(vector <CNode> &l_node);
    CNode lastOpen();
    void saveRoute();
    void optimizeRoute();

public:
    CGenerateRoute(CMap &map);
    ~CGenerateRoute();

    CRoute simpleRoute(CNode i_node, CNode f_node);
    std::vector<CRoute> multRoutes(std::vector<CNodes> l_nodes);
    bool changeMap(CMap map);
};

#endif /*__CGenerateRoute__*/
