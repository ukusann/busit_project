#include "CMap.h"
#include <iostream>
#include <stdexcept>

#define  DIR_INPUT_MAP  "../maps/input_maps/"
#define  DIR_SAVE_MAP   "../maps/saved_maps/"
#define  F_TYPE_TXT     ".txt"

#define BS_MASK 0x40
using namespace std;

//===========================================================
//===========================================================
// ***********Beginning of Constructor/Destructor: **********

CMap::CMap(uint8_t map_id)
{

    this->map       = new vector<vector<CNode>>(0);
    this->map_id    = map_id;
    this->file_name = "";
    this->len_i     = 0;
    this->len_j     = 0; 
}

CMap::~CMap()
{
   delete this->map;
}

// ***********End of Constructor/Destructor: ****************
//===========================================================
//===========================================================
// ***********Beginning of Private Functions: ***************

bool CMap::loadMapFile(string file_name)
{
    bool flag = true;
    ifstream rd_map_file;

    rd_map_file.open(file_name, ifstream::in);
    if (!rd_map_file)
    {
        flag = false;
        cout << "Error opening the input file: " << DIR_INPUT_MAP + file_name + F_TYPE_TXT << endl;
    }
    else 
    {
        uint16_t temp_len_i;
        uint16_t temp_len_j;

        rd_map_file >> temp_len_j >> temp_len_i;
        
        if (temp_len_i < 0 && temp_len_j < 0)
        {
            cout << "ERROR: Invalid map length" << endl;
            flag = false;
        }
        else
        {
            len_i = temp_len_i; // y
            len_j = temp_len_j; // x
            unsigned int id = 1;
            for (uint16_t i = 0 ; i < len_i ; i++)
            {
                vector<CNode> map_temp;

                for (uint16_t j = 0 ; j < len_j ; j++)
                {       
                    unsigned int temp_byte_info;
                    rd_map_file >> temp_byte_info;

                    map_temp.push_back( CNode( id++ , temp_byte_info, j, i) );
                    
                }
                map->push_back(map_temp);
            }
        }
    }
    return flag;
}

//-----------------------------------------------------------
//-----------------------------------------------------------

bool CMap::saveMap()
{
    bool flag = true;
    
    this->file_map.open(DIR_SAVE_MAP + this->file_name + F_TYPE_TXT, ofstream::out);
    
    if (!this->file_map)
        flag = false;
    else
    {
        this->file_map << len_j << " " << len_i << endl;

       for (vector<vector<CNode>>::iterator itr = map->begin(); itr != map->end(); itr++)
        {
            vector<CNode> tl = *itr;

            for (vector<CNode>::iterator it = tl.begin(); it != tl.end(); it++)
            {
               this->file_map <<  it->getNodeInfo() << " ";
                
            }
            this->file_map << endl;
        }
        this->file_map.close();
    }
    return flag;
}

// ***********End of Private Functions: *********************
//===========================================================
//===========================================================
// ***********Beginning of Public Functions: ****************


bool CMap::inputMap(string file_name)
{

    bool flag = true;
    string file = "";
    
    if (file_name == this->file_name)  { file = DIR_SAVE_MAP  + file_name + F_TYPE_TXT; }

    else { file = DIR_INPUT_MAP + file_name + F_TYPE_TXT; this->file_name = file_name; }
        
    if( !(CMap::loadMapFile(file)) )
        flag = false;
    else 
        if(CMap::saveMap())
            cout << "Map Saved" << endl;

    return flag;
}


//-----------------------------------------------------------
//-----------------------------------------------------------

//**************** Byte Info *********************

void CMap::mapNodeOpen(SCoord pos){
    this->map->at(pos.y).at(pos.x).openNode();
}

void CMap::mapNodeClose(SCoord pos){
    this->map->at(pos.y).at(pos.x).closeNode();
}

void CMap::mapNodeOpen(unsigned int x, unsigned int y){
    this->map->at(y).at(x).openNode();
}

void CMap::mapNodeClose(unsigned int x, unsigned int y){
    this->map->at(y).at(x).closeNode();
}

void CMap::mapBusStop(SCoord pos, bool flag){
    unsigned short int b_inf = this->map->at(pos.y).at(pos.x).getNodeInfo();
    if (flag){
        this->map->at(pos.y).at(pos.x).setNodeInfo(b_inf | BS_MASK );
    }else
        this->map->at(pos.y).at(pos.x).setNodeInfo(b_inf & (~BS_MASK) );
}

void CMap::mapBusStop(unsigned int x, unsigned int y, bool flag){
    unsigned short int b_inf = this->map->at(y).at(x).getNodeInfo();
    if (flag){
        this->map->at(y).at(x).setNodeInfo(b_inf | BS_MASK );
    }else
        this->map->at(y).at(x).setNodeInfo(b_inf & (~BS_MASK) );
}

bool CMap::mapIsBusStop(SCoord pos){
    unsigned short int b_inf = this->map->at(pos.y).at(pos.x).getNodeInfo();
    if (b_inf & BS_MASK == 0)
        return false;
    else
        return true;
}

bool CMap::mapIsBusStop(unsigned int x, unsigned int y){
    unsigned short int b_inf = this->map->at(y).at(x).getNodeInfo();
    if (b_inf & BS_MASK == 0)
        return false;
    else
        return true;
}

//____________________________________________________

//**************** Gets and Sets *********************

//--------------------- Get ID -----------------------
SCoord CMap::getMapLen(){
    SCoord coord_len = {this->len_j, this->len_i };
    return coord_len;
}

//-------- Get desired Node on the map[y][x]  --------
bool  CMap::getMapNode( unsigned short int x, unsigned short int y, CNode &_pnode ){
    bool flag = false;
    
    if(x >= 0 && y >= 0 && x < this->len_j && y < this->len_i){
        flag = true;
        // _pnode = &this->pmap[y].at(x);
        _pnode = this->map->at(y).at(x);
        //cout << "get map node" << endl;
    }
    return flag;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool  CMap::getMapNode( SCoord pos, CNode &_pnode ){
    bool flag = false;
    if(pos.x >= 0 && pos.y >= 0 && pos.x <= this->len_j && pos.y <= this->len_i){
        flag = true;
        _pnode = this->map->at(pos.y).at(pos.x);
    }
    return flag;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

string  CMap::printMap(){
    string s;

    s.append( "\r\n\t\t\t\t * MAP: " + this->file_name + " *\r\n\r\n");
    for(int i = 0 ; i < this->len_i ; i++ ){
        s.append("| ");
         
        for(int j = 0 ; j < this->len_j ; j++ ){
            unsigned int bi = this->map->at(i).at(j).getNodeInfo();
            if (bi < 1)
                s.append("   ");
            else if(!this->map->at(i).at(j).isOpen())
                s.append(" --");
            else if((bi & BS_MASK ) > 0)
                s.append(" BS");
            else if( (bi & 15) < 10){
                s.append("  ");
                s.append(to_string(bi));
            }else{
                s.append(" ");
                s.append(to_string(bi));
            }
        }
        s.append("  |\r\n");
    }
    return s;
}
// ***********End of Public Functions: **********************
//===========================================================
//===========================================================
