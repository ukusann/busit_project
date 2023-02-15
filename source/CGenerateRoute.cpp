#include "CGenerateRoute.h"
#include<iostream>


#define M_JUMP_DOWN     0x2e   // 0010 1110
#define M_JUMP_UP       0x1d   // 0001 1101
#define M_JUMP_RIGHT    0x8b   // 1000 1011
#define M_JUMP_LEFT     0x47   // 0100 0111
#define M_RESERVED_BUS  0x20   // 0010 0000

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
bool CGenerateRoute::makeRoute( CNode i_node, CNode f_node, bool opt, unsigned short int max_g)
{
    vector<CNode> next_node;
    CNode *pnode = new CNode;
    
    unsigned short int gain = 0;            
    bool r_finished         = true;
    SCoord i_pos            = i_node.getPos();
    
    if(!this->pmap_info->getMapNode(i_pos, *pnode))
    {
        cout << "ERROR GETMAPNODE!" << endl;
        r_finished = false; //! ***ERROR Throw here!***
        return r_finished;
    }
    
    if(opt)
        gain = this->single_route->Mem_route.size();
    else
    {
        pnode->closeNode();                             // Close the Node
        next_node.push_back(*pnode);
        single_route->Mem_route.push_back(next_node);   // Add to Route memory
        gain ++;
    }
    
    //cout << "ID of pnode: " << pnode->getId() << " ID of f_node: " << f_node.getId() << "gain: " << gain << endl;
    while (pnode->getId() != f_node.getId() && r_finished == true)
    {
        next_node = CGenerateRoute::openNodes(pnode);    // Open the nodes
        
        CGenerateRoute::decisionDir(next_node, pnode);   // Decision: directions
        
        if (opt && (gain >= max_g )){ r_finished = false; /*ERROR*/ break;} 
        
        unsigned int nx_size = next_node.size();
        if (nx_size > 0)
        {
            //cout << "Bigger than 0\n\n" << endl;
            if (nx_size > 1){                                // if more than 1 node is open...
                decisionDistReservedBus(next_node,&f_node);   // make a decision
            //    cout << "Bigger than 1\n\n" << endl;
            }
            next_node[0].closeNode();
            SCoord tpos = next_node[0].getPoint();

            this->pmap_info->mapNodeClose( tpos );
            this->pmap_info->getMapNode(tpos,*pnode);
            
            single_route->Mem_route.push_back(next_node);   // save's it in the memory
            next_node.clear();                              // clears the vector
            gain ++;
        }
        else
        {
        //    cout << "less than 0\n\n" << endl;
            gain = CGenerateRoute::lastOpen(*pnode);
          
            if(gain == 0)
            {
                r_finished = false;
                // --------------------
                // ERROR
                // --------------------
                break;
            }
        }
      //  cout << "ID of pnode: " << pnode->getId() << " ID of f_node: " << f_node.getId() << " gain : "<< gain << endl;
        
    }

    if (r_finished)   // if no ERROR occurred, saves the route
        CGenerateRoute::saveRoute();
    
    return r_finished;
}
//____________________________________________________
//------------------ Open Condition ------------------
bool CGenerateRoute::openCondition(short int x, short int y)
{
    CNode *node_temp = new CNode;
    bool flag  = false;
    

    if(pmap_info->getMapNode(x, y, *node_temp))                      // The node on this positions exists?
    {  
        if(node_temp->isOpen() && node_temp->getNodeInfo() != 0)    // Is the node close? Is it a wall?
            flag = true;     
    }
    return flag;
}

//____________________________________________________
//------------------ Open Nodes ----------------------

vector<CNode> CGenerateRoute::openNodes(CNode *pnodes)
{
    vector<CNode> temp_nodes;
    CNode *temp_pnode = new CNode;
    SCoord ppos = pnodes->getPos();
   // cout<< "openNodes:" << endl;
    if(CGenerateRoute::openCondition( (short int)(ppos.x +1), (short int)(ppos.y) )) // Right of the node pointer
    {
        if(pmap_info->getMapNode(ppos.x+1, ppos.y, *temp_pnode)){
            temp_nodes.push_back(*temp_pnode);
    //        cout << "saved node 1 \n";
            }
    }
    if(CGenerateRoute::openCondition( (short int)(ppos.x -1), (short int)(ppos.y) )) // Left of the node pointer
    {
        if(pmap_info->getMapNode(ppos.x-1, ppos.y, *temp_pnode)){
            temp_nodes.push_back(*temp_pnode);
    //        cout << "saved node 2 \n";
            }
    }
    if(CGenerateRoute::openCondition( (short int)(ppos.x), (short int)(ppos.y +1) )) // Down of the node pointer
    {
        if(pmap_info->getMapNode(ppos.x, ppos.y +1, *temp_pnode));{
            temp_nodes.push_back(*temp_pnode);
    //        cout << "saved node 3 \n";
        }
    }
    if(CGenerateRoute::openCondition( (short int)(ppos.x), (short int)(ppos.y -1) )) // Up of the node pointer
    {
        if(pmap_info->getMapNode(ppos.x, ppos.y -1, *temp_pnode));{
           temp_nodes.push_back(*temp_pnode);
    //       cout << "saved node 4 \n";
           }
    }
    return temp_nodes;
}

//____________________________________________________
//---------------- Decision Direction ----------------
void CGenerateRoute::decisionDir(vector <CNode> &n_node, CNode *pnode)
{
    for( unsigned int i = 0 ; i < n_node.size() ; i++)  // The node only has one direction? and it is backwards? 
    {
        uint8_t dir_mask = CGenerateRoute::directionMask(pnode->getPos(), n_node[i].getPos());
        
        if( (pnode->getNodeInfo() & ((dir_mask & 0xF0) >> 4)) == 0 || 
            (n_node[i].getNodeInfo() & dir_mask & 0x0F) == 0 )
        {
            n_node.erase(n_node.begin() + i--);
       //     cout << "node remove \n";
        }
  //      cout << endl;
    }
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
    //cout << "\n\n\n  <<<<< dicision >>>>> \n\n\n";
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
        else if ( (node_info0 & M_RESERVED_BUS) == 0 &&  (node_info1 & M_RESERVED_BUS) == M_RESERVED_BUS )
            bubble_sort = true;

        if (bubble_sort)
        {
            CNode temp_n = nx_node[i];
            nx_node[i] = nx_node[i+1];
            nx_node[i+1] = temp_n; 
        }
    }
    //cout << "\n\n\n  <<<<< dicision >>>>> \n\n\n";
}

//____________________________________________________
//---------------- Last Open node --------------------
unsigned short int CGenerateRoute::lastOpen(CNode &pnode)
{
    SCoord pos;
    unsigned short int mem_len = single_route->Mem_route.size(); 
    
    for ( int i = mem_len -1 ; i > 0; i-- )
    {
        unsigned short int len_j = single_route->Mem_route[i].size();
        for(unsigned short int j = 0 ; j < len_j ; j++)
        {
            pos = single_route->Mem_route.at(i).at(j).getPoint();
            if (single_route->Mem_route.at(i).at(j).isOpen())
            {
                if(this->pmap_info->getMapNode(pos, pnode))
                {
                    CNode temp = single_route->Mem_route.at(i).at(j);
                    single_route->Mem_route.at(i).at(j) = single_route->Mem_route.at(i).at(0);
                    single_route->Mem_route.at(i).at(0) = temp;

          //          cout << "Node found! ID = "<< pnode.getId() << endl;
                    single_route->Mem_route.at(i).at(0).closeNode();
                    this->pmap_info->mapNodeClose(pos);
                    pnode.closeNode();
                }
                return (unsigned short int)i;  // Return gain
            }    
        }
        
        for(unsigned short int j = 0 ; j < len_j ; j++){    // OPENS all closed nodes
            pos = single_route->Mem_route.at(i).at(j).getPoint();
            this->pmap_info->mapNodeOpen(pos);
        //    cout << "remove node AT  x = " << pos.x << " y = " << pos.y << endl;
        }
        single_route->Mem_route.erase(single_route->Mem_route.begin() +single_route->Mem_route.size() ); // Erase the node
    }
    return 0;
}

//____________________________________________________
//------------------ Save Route ----------------------
void CGenerateRoute::saveRoute()
{
    unsigned short int mem_len = this->single_route->Mem_route.size();
    this->single_route->Route.clear();

    //cout << "Save Route :" << endl;
    for(unsigned short int i = 0 ; i < mem_len ; i++ ){
        
        this->single_route->Route.push_back(this->single_route->Mem_route.at(i).at(0));
      //  cout << " (" << single_route->Route[i].getId() << ") ";
    }
    return;
}

//____________________________________________________
//---------------- Optimize Route --------------------
void CGenerateRoute::optimizeRoute()
{
    vector<vector<CNode>> temp_mem = single_route->Mem_route;
    CNode temp_pnode;

    unsigned short int gain         = single_route->Route.size();
    unsigned short int total_gain   = gain -2;
    CNode f_node                    = this->single_route->Route.at(gain-1);
   // cout << "\n\nOptizime route --- total gain = " << total_gain <<" f_node id = " << f_node.getId() << endl;
    gain = lastOpen(temp_pnode);

   // cout << "current gain: " << gain << " node ID: " << temp_pnode.getId() << "\n\n";
    while(gain != 0)
    {
        if(CGenerateRoute::makeRoute(temp_pnode, f_node, ENABLE_OPTIMIZATION, total_gain))
        {
            temp_mem   = single_route->Mem_route;
            total_gain = single_route->Route.size();
        }
        
        gain = lastOpen(temp_pnode);
    }
    this->single_route->Mem_route = temp_mem;
    return;
}

//____________________________________________________
//------------------ Reset Map -----------------------
void CGenerateRoute::resetMap()  {  // open all nodes
    SCoord len = this->pmap_info->getMapLen();
    for (unsigned int i = 0 ; i < len.y; i++)
        for (unsigned int j = 0 ; j < len.x; j++){
            this->pmap_info->mapNodeOpen(j, i);
        }

}

//====================================================
//====================================================
//**************** Public Funtions *******************
//____________________________________________________
//---------------- Simple Route ----------------------
CRoute CGenerateRoute::simpleRoute(CNode i_node, CNode f_node, unsigned short int id)
{
    bool err_flag = false;
    single_route = new CRoute();
    CRoute route(id);
    //-----------------------
    //      Mutex wait -> pmap (CMap)
    //-----------------------

    if(CGenerateRoute::makeRoute(i_node,f_node,DISABLE_OPTIMIZATION, 0)){
        CGenerateRoute::optimizeRoute();
        route = *single_route;
        
        }
    else
        {err_flag = true;}
        int gain =route.getTotalGain();
    if(!err_flag){ 
        for (int a = 0 ; a < gain ; a++){
            CNode n = route.getNode(a);
            SCoord c = n.getPos();
            this->pmap_info->mapNodeClose(c);
        }

        cout << "\n" << this->pmap_info->printMap() << endl;
    
        CGenerateRoute::resetMap();
        
    }
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
    unsigned short int size_ln = l_nodes.size();
    for(unsigned short int i = 0 ; i < size_ln -1 ; i++){
        vr.push_back(simpleRoute(l_nodes[i], l_nodes[i+1], i+1));
  //      cout << "begin -> " << l_nodes[i].getId() << ", end -> " << l_nodes[i+1].getId() << endl;
    }

    return vr;
}

//____________________________________________________
//------------------ Change Map ----------------------
void CGenerateRoute::changeMap(CMap *pmap)
{
    this->pmap_info = pmap;
}
