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
    
    pnode->closeNode();
     this->single_route->mem_route.insert(*pnode);
        

    return r_finished;
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