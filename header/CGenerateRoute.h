#ifndef __CGenerateRoute__
#define __CGenerateRoute__

#include "CRoute.h"
#include "CMap.h"
#include <vector>

class CGenerateRoute 
{
private:
    CRoute *single_route;
    std::vector<CRoute> multi_route;
    CMap *pmap_info;

    bool make_route(CNode i_node, CNode f_node,
                    bool opt, unsigned short int max_g);
    
    std::vector<CNode> openNodes(CNode *pnodes);
    bool openCondition(short int x, short int y);

    CNode decisionDir(std::vector <CNode> &l_node, CNode *pnode);
    unsigned short int directionMask(SCoord ppos, SCoord nxpos);   
    void decisionDistReservedBus(std::vector <CNode> &l_node, CNode *pnode_f);
    
    CNode lastOpen();
    void saveRoute();
    void optimizeRoute();

public:
    CGenerateRoute();
    ~CGenerateRoute();

    CRoute simpleRoute(CNode i_node, CNode f_node);
    std::vector<CRoute> multRoutes(std::vector<CNode> l_nodes);
    bool changeMap(CMap map);
};

#endif /*__CGenerateRoute__*/
