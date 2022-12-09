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

    bool makeRoute(CNode i_node, CNode f_node,
                    bool opt, unsigned short int max_g);
    
    std::vector<CNode> openNodes(CNode *pnodes);
    bool openCondition(short int x, short int y);

    CNode decisionDir(std::vector <CNode> &l_node, CNode *pnode);
    unsigned short int directionMask(SCoord ppos, SCoord nxpos);   
    void decisionDistReservedBus(std::vector <CNode> &l_node, CNode *pnode_f);
    
    unsigned short int lastOpen(CNode *pnode);
    void saveRoute();
    void optimizeRoute();

public:
    CGenerateRoute(CMap *pmap, CRoute *route);
    ~CGenerateRoute();

    CRoute simpleRoute(CNode i_node, CNode f_node, unsigned short int id);
    std::vector<CRoute> multRoutes(std::vector<CNode> l_nodes);
    void changeMap(CMap *pmap);
};

#endif /*__CGenerateRoute__*/
