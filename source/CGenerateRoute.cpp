#include "CGenerateRoute.h"

#define M_JUMP_DOWN     14   // 0000 1110
#define M_JUMP_UP       13   // 0000 1101
#define M_JUMP_RIGHT    11   // 0000 1011
#define M_JUMP_LEFT      7   // 0000 0111
#define M_RESERVED_BUS  32   // 0010 0000

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
    next_node.push_back(*pnode);
    single_route->mem_route.push_back(next_node);   // Add to Route memory

    while (pnode->getId() != f_node.getId()){
        
        gain ++;
        next_node = CGenerateRoute::openNodes(pnode);
        CGenerateRoute::decisionDir(next_node, pnode);
        
        if (opt && (gain < max_g )){ break;}
        
        unsigned int nx_size = next_node.size();
        if (nx_size == 0){ pnode = &next_node[0];}
        else if (nx_size > 1){ decisionDistReservedBus(next_node,pnode);}
        else{}
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
//---------------- Decision Direction ----------------
CNode CGenerateRoute::decisionDir(vector <CNode> &l_node, CNode *pnode){

    for( unsigned int i = 0 ; i < l_node.size() ; i++)
        if(l_node[i].getNodeInfo() & CGenerateRoute::directionMask(pnode->getPos(), l_node[i].getPos()) == 0)
            l_node.erase(l_node.begin() +i);
}

//____________________________________________________
//---------------- Direction Mask --------------------
unsigned short int CGenerateRoute::directionMask(SCoord ppos, SCoord nxpos){
 
    unsigned short int mask = 0;
    if ((nxpos.x - ppos.x) == 0)
        if(nxpos.y < ppos.y)
            mask = M_JUMP_DOWN;
        else
            mask = M_JUMP_UP;
    else        
        if(nxpos.x < ppos.x)
            mask = M_JUMP_RIGHT;
        else
            mask = M_JUMP_LEFT;
}
//____________________________________________________
//---------------- Decision Distance -----------------
void CGenerateRoute::decisionDistReservedBus(vector <CNode> &nx_node, CNode *pnode_f){

    for(unsigned int i = 0 ; i < (nx_node.size()-1) ; i++ ){

        bool bubble_sort = false;
        SCoord pos_f = pnode_f->getPos();
        float dist_0 = nx_node[i   ].getDistance(pos_f);
        float dist_1 = nx_node[i +1].getDistance(pos_f);
        uint16_t node_info0 = nx_node[i   ].getNodeInfo();
        uint16_t node_info1 = nx_node[i +1].getNodeInfo();

        if(dist_0 > dist_1)
            bubble_sort = true;
        else if (node_info0 & M_RESERVED_BUS == 0 &&  node_info1 & M_RESERVED_BUS == M_RESERVED_BUS )
            bubble_sort = true;

        if (bubble_sort){
            CNode temp_n = nx_node[i];
            nx_node[i] = nx_node[i+1];
            nx_node[i+1] = temp_n; 
        }
    }
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