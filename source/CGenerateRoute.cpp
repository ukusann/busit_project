#include "CGenerateRoute.h"
#include<iostream>


#define M_JUMP_DOWN     14   // 0000 1110
#define M_JUMP_UP       13   // 0000 1101
#define M_JUMP_RIGHT    11   // 0000 1011
#define M_JUMP_LEFT      7   // 0000 0111
#define M_RESERVED_BUS  32   // 0010 0000

#define ENABLE_OPTIMIZATION  true
#define DISABLE_OPTIMIZATION false

using namespace std;

//============ Constructor and Destructor ============

CGenerateRoute::CGenerateRoute(CMap *pmap, CRoute *route){
    this->pmap_info     = pmap;
    this->single_route  = route;
}

//------------------------------------------------
CGenerateRoute::~CGenerateRoute(){
    this->pmap_info     = nullptr;
    this->single_route  = nullptr;   
}

//====================================================
//====================================================
//**************** Private Funtions ******************
//____________________________________________________
//------------------ Make Route ----------------------
bool CGenerateRoute::makeRoute(CNode &i_node, CNode &f_node, bool opt, unsigned short int max_g)
{
    vector<CNode> next_node;
    CNode *pnode;
    
    unsigned short int gain = 0;            
    bool r_finished         = true;
    SCoord i_pos            = i_node.getPos();
    cout << "Before getMapNode\n";
    if(!this->pmap_info->getMapNode(i_pos.x, i_pos.y, *pnode))
    {
        cout << "ERROR GETMAPNODE!" << endl;
        r_finished = false; //! ***ERROR Throw here!***
        return r_finished;
    }
    cout << "After getMapNode\n";

    if(opt)
        gain = this->single_route->pMem_route->size();
    else
    {
        pnode->closeNode();                             // Close the Node
        next_node.push_back(*pnode);
        single_route->pMem_route->push_back(next_node);   // Add to Route memory
    }
    
    while (pnode->getId() != f_node.getId() && r_finished == true)
    {
        
        gain ++;
        next_node = CGenerateRoute::openNodes(pnode);    // Open the nodes 
        CGenerateRoute::decisionDir(next_node, pnode);   // Decision: directions
        
        if (opt && (gain < max_g )){ r_finished = false; /*ERROR*/ break;} 
        
        unsigned int nx_size = next_node.size();
        if (nx_size > 0)
        {
            if (nx_size > 1)                                // if more than 1 node is open...
                decisionDistReservedBus(next_node,pnode);   // make a decision
            pnode = &next_node[0];                          // pnode points to the new node
            pnode->closeNode();                             // close it
            single_route->pMem_route->push_back(next_node);   // save's it in the memory
            next_node.clear();                              // clears the vector
        }
        else
        {
            gain = CGenerateRoute::lastOpen(pnode);
            if(gain == 0)
            {
                r_finished = false;
                // --------------------
                // ERROR
                // --------------------
                break;
            }
        }
    }

    if (r_finished)   // if no ERROR occurred, saves the route
        CGenerateRoute::saveRoute();

    return r_finished;
}
//____________________________________________________
//------------------ Open Condition ------------------
bool CGenerateRoute::openCondition(short int x, short int y)
{
    CNode *node_temp;
    bool flag  = false;
    SCoord len = pmap_info->getMapLen();
    

    if(pmap_info->getMapNode(x, y, *node_temp))                      // The node on this positions exists?
        if(node_temp->isOpen() && node_temp->getNodeInfo() != 0)    // Is the node close? Is it a wall?
            flag = true;     
    return flag;
}

//____________________________________________________
//------------------ Open Nodes ----------------------

vector<CNode> CGenerateRoute::openNodes(CNode *pnodes)
{
    vector<CNode> temp_nodes;
    CNode *temp_pnode;
    SCoord ppos = pnodes->getPos();

    if(CGenerateRoute::openCondition( (short int)(ppos.x +1), (short int)(ppos.y) )) // Right of the node pointer
        if(pmap_info->getMapNode(ppos.x+1, ppos.y, *temp_pnode))
            temp_nodes.push_back(*temp_pnode);
    
    if(CGenerateRoute::openCondition( (short int)(ppos.x -1), (short int)(ppos.y) )) // Left of the node pointer
        if(pmap_info->getMapNode(ppos.x-1, ppos.y, *temp_pnode))
            temp_nodes.push_back(*temp_pnode);
    
    if(CGenerateRoute::openCondition( (short int)(ppos.x), (short int)(ppos.y +1) )) // Down of the node pointer
        if(pmap_info->getMapNode(ppos.x, ppos.y +1, *temp_pnode));
            temp_nodes.push_back(*temp_pnode);
    
    if(CGenerateRoute::openCondition( (short int)(ppos.x), (short int)(ppos.y -1) )) // Up of the node pointer
        if(pmap_info->getMapNode(ppos.x, ppos.y -1, *temp_pnode));
           temp_nodes.push_back(*temp_pnode);
    
    return temp_nodes;
}

//____________________________________________________
//---------------- Decision Direction ----------------
void CGenerateRoute::decisionDir(vector <CNode> &l_node, CNode *pnode)
{
    for( unsigned int i = 0 ; i < l_node.size() ; i++)  // The node only has one direction? and it is backwards? 
        if(l_node[i].getNodeInfo() & CGenerateRoute::directionMask(pnode->getPos(), l_node[i].getPos()) == 0)
            l_node.erase(l_node.begin() +i);
}

//____________________________________________________
//---------------- Direction Mask --------------------
unsigned short int CGenerateRoute::directionMask(SCoord ppos, SCoord nxpos)
{
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
    
    return mask;
}
//____________________________________________________
//----- Decision Distance and Bus Reserved Road! -----

// Ordenates the vector next_node by the most priority decision to the least
void CGenerateRoute::decisionDistReservedBus(vector <CNode> &nx_node, CNode *pnode_f)
{
    for(unsigned int i = 0 ; i < (nx_node.size()-1) ; i++ )
    {
        bool bubble_sort    = false;
        SCoord pos_f        = pnode_f->getPos();
        float dist_0        = nx_node[i   ].getDistance(pos_f);
        float dist_1        = nx_node[i +1].getDistance(pos_f);
        uint16_t node_info0 = nx_node[i   ].getNodeInfo();
        uint16_t node_info1 = nx_node[i +1].getNodeInfo();

        if(dist_0 > dist_1)
            bubble_sort = true;
        else if (node_info0 & M_RESERVED_BUS == 0 &&  node_info1 & M_RESERVED_BUS == M_RESERVED_BUS )
            bubble_sort = true;

        if (bubble_sort)
        {
            CNode temp_n = nx_node[i];
            nx_node[i] = nx_node[i+1];
            nx_node[i+1] = temp_n; 
        }
    }
}

//____________________________________________________
//---------------- Last Open node --------------------
unsigned short int CGenerateRoute::lastOpen(CNode *pnode)
{
    unsigned short int mem_len = single_route->pMem_route->size(); 
    
    for ( int i = mem_len -1 ; i >= 0; i-- )
    {
        for(unsigned short int j = 0 ; j < single_route->pMem_route[i].size(); j++)
        {
            if (single_route->pMem_route->at(i).at(j).isOpen())
            {
                SCoord pos = single_route->pMem_route->at(i).at(j).getPoint();
                if(this->pmap_info->getMapNode(pos.x, pos.y, *pnode))
                {
                    pnode->closeNode();
                    single_route->pMem_route->erase(single_route->pMem_route->begin() +(mem_len -i ),
                                              single_route->pMem_route->end());
                }
                return (unsigned short int)i;
            }
        }
    }
    return 0;
}

//____________________________________________________
//------------------ Save Route ----------------------
void CGenerateRoute::saveRoute()
{
    unsigned short int mem_len = this->single_route->pMem_route->size();
    this->single_route->pRoute->clear();

    for(unsigned short int i = 0 ; i < mem_len ; i++ )
        this->single_route->pRoute->push_back(this->single_route->pMem_route->at(i).at(0));
    return;
}

//____________________________________________________
//---------------- Optimize Route --------------------
void CGenerateRoute::optimizeRoute()
{
    vector<vector<CNode>> *temp_mem;
    CNode *temp_pnode;

    unsigned short int gain         = single_route->pRoute->size();
    unsigned short int total_gain   = gain;
    CNode f_node                    = this->single_route->pRoute->at(gain-1);

    gain = lastOpen(temp_pnode);

    while(gain != 0)
    {
        if(CGenerateRoute::makeRoute(*temp_pnode, f_node, ENABLE_OPTIMIZATION, total_gain))
        {
            temp_mem   = single_route->pMem_route;
            total_gain = single_route->pRoute->size();
        }
        
        gain = lastOpen(temp_pnode);
    }
    this->single_route->pMem_route = temp_mem;
    return;
}


//====================================================
//====================================================
//**************** Public Funtions *******************
//____________________________________________________
//---------------- Simple Route ----------------------
CRoute CGenerateRoute::simpleRoute(CNode &i_node, CNode &f_node, unsigned short int id)
{
    CRoute route(id);
    bool err_flag = false;
    //-----------------------
    //      Mutex wait -> pmap (CMap)
    //-----------------------
    cout << "Before makeroute\n";
    if(CGenerateRoute::makeRoute(i_node,f_node,DISABLE_OPTIMIZATION, 0))
        {
            cout << "After makeroute and before optmization\n";
            CGenerateRoute::optimizeRoute();
            cout << "After optimization\n";
        }
            
    else
        err_flag = true;
    
    //-----------------------
    //      Mutex release -> pmap (CMap)
    //-----------------------

    
    return route;
}

//____________________________________________________
//---------------- Multiple Route --------------------
vector<CRoute> CGenerateRoute::multRoutes(vector<CNode> l_nodes)
{
    vector<CRoute> vr;
    return vr;
}

//____________________________________________________
//------------------ Change Map ----------------------
void CGenerateRoute::changeMap(CMap *pmap)
{
    this->pmap_info = pmap;
}