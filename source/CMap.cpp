#include "CMap.h"
#include <iostream>
#include <stdexcept>

#define  DIR_INPUT_MAP  "../maps/input_maps/"
#define  DIR_SAVE_MAP   "../maps/saved_maps/"
#define  F_TYPE_TXT     ".txt"

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
    CMap::inputMap(file_name);
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
        unsigned short int id = 1;

        rd_map_file >> temp_len_j >> temp_len_i;
        
        if (temp_len_i < 0 && temp_len_j < 0)
        {
            cout << "ERROR: Invalid map length" << endl;
            flag = false;
        }
        else
        {
            len_i = temp_len_i;
            len_j = temp_len_j;
            unsigned short int id = 1;
            for (uint16_t j = 0 ; j < len_j ; j++)
            {
                vector<CNode> map_temp;

                for (uint16_t i = 0 ; i < len_i ; i++)
                {
                    
                    unsigned int temp_byte_info;
                    rd_map_file >> temp_byte_info;

                    map_temp.push_back( CNode( id++ , temp_byte_info, j, i) );
                    
                    //cout << temp_byte_info << " ";

                    //cout << map_temp[i].getNodeInfo() << " ";
                }
                // cout << endl;
                map->push_back(map_temp);
            }
            cout << this->file_name << endl;
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

//____________________________________________________

//**************** Gets and Sets *********************

//--------------------- Get ID -----------------------
SCoord CMap::getMapLen(){
    SCoord coord_len = {this->len_j, this->len_i };
    return coord_len;
}

//-------- Get desired Node on the map[y][x]  --------
bool  CMap::getMapNode( unsigned short int x, unsigned short int y, CNode &_pnode){
    bool flag = false;
    
    if(x >= 0 && y >= 0 && x <= this->len_j && y <= this->len_i){
        flag = true;
        // _pnode = &this->pmap[y].at(x);
        cout << "Before pnode atribution\n";
        _pnode = this->map->at(y).at(x);
        cout << "After pnode atribution\n";
        
    }
    return flag;
}


// ***********End of Public Functions: **********************
//===========================================================
//===========================================================
