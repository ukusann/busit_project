#include "CGenerateRoute.h"

using namespace std;

//============ Constructor and Destructor ============

CGenerateRoute::CGenerateRoute(){
}

//------------------------------------------------
CGenerateRoute::~CGenerateRoute(){}

//====================================================
//====================================================
//**************** Private Funtions ******************
//____________________________________________________
//------------------ Make Route ----------------------
bool CGenerateRoute::make_route( CNode i_node, CNode f_node, bool opt, unsigned short int max_g)
{
    unsigned short int gain = 0;
    vector<CNode> next_node;
    CNode *pnode = &i_node; 
    bool r_finished = false;

    if(opt)
        gain = this->single_route->mem_route.size();
    
    pnode->closeNode();                             // Close the Node
    single_route->mem_route.push_back(next_node.push_back(*pnode));   // Add to Route memory

    while (pnode->getId() != f_node.getId()){
        
        gain ++;
        next_node.push_back(CGenerateRoute::openNodes(pnode));
    }


    return r_finished;
}
//____________________________________________________
//------------------ Open Condition ------------------
bool CGenerateRoute::openCondition(short int x, short int y){
    bool flag = false;
    SCoord len = pmap_info->getMapLen();
    CNode node_temp = pmap_info->getMapNode(x, y);

    if(&node_temp != NULL)
        if(node_temp.isOpen() && node_temp.getNodeInfo() != 0)
            flag = true;     
    return flag;
}

//____________________________________________________
//------------------ Open Nodes ----------------------

vector<CNode> CGenerateRoute::openNodes(CNode *pnodes){
    vector<CNode> temp_nodes;
    SCoord ppos = pnodes->getPos();

    if(CGenerateRoute::openCondition( (short int)(ppos.x +1), (short int)(ppos.y) ))
        temp_nodes.push_back(pmap_info->getMapNode(ppos.x+1, ppos.y));
    
    if(CGenerateRoute::openCondition( (short int)(ppos.x -1), (short int)(ppos.y) ))
        temp_nodes.push_back(pmap_info->getMapNode(ppos.x-1, ppos.y));
    
    if(CGenerateRoute::openCondition( (short int)(ppos.x), (short int)(ppos.y +1) ))
        temp_nodes.push_back(pmap_info->getMapNode(ppos.x, ppos.y +1));
    
    if(CGenerateRoute::openCondition( (short int)(ppos.x), (short int)(ppos.y -1) ))
        temp_nodes.push_back(pmap_info->getMapNode(ppos.x, ppos.y -1));
        
    return temp_nodes;
}

//____________________________________________________
//---------------- Decision Maker --------------------
CNode CGenerateRoute::decisionMaker(vector <CNode> &l_node){
    CNode n(5,12,1,1);
    return n;
}

//____________________________________________________
//---------------- Last Open node --------------------
CNode CGenerateRoute::lastOpen(){
    CNode n(5,12,1,1);
    return n;
}

//____________________________________________________
//------------------ Save Route ----------------------
void CGenerateRoute::saveRoute(){
    return;
}

//____________________________________________________
//---------------- Optimize Route --------------------
void CGenerateRoute::optimizeRoute(){
    return;
}


//====================================================
//====================================================
//**************** Public Funtions *******************
//____________________________________________________
//---------------- Simple Route ----------------------
CRoute CGenerateRoute::simpleRoute(CNode i_node, CNode f_node){
    CRoute r(1);
    return r;
}

//____________________________________________________
//---------------- Multiple Route --------------------
vector<CRoute> CGenerateRoute::multRoutes(vector<CNode> l_nodes){
    vector<CRoute> vr;
    return vr;
}

//____________________________________________________
//------------------ Change Map ----------------------
bool CGenerateRoute::changeMap(CMap map){
    return false;
}