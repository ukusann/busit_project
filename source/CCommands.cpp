
/*
" <<<<<<<<<<<<<<<<<<<<<<< Manual Commands >>>>>>>>>>>>>>>>>>>>>>>>\n\n"

"ADBU [id x1 y1 ... xn yn]  -> Add Bus\n"
"ADBS [id x y]              -> Add Bus Stop\n"
"EBID [id id_new]           -> Edit Bus ID\n"
"EBDR [id x1 y1 ... xn yn]  -> Edit Bus Default Route\n"
"EBRM [id]                  -> Remove Bus\n"
"ESID [id id_new]           -> Edit Bus Stop ID\n"
"ESRM [id]                  -> Remove Bus Stop\n"
"URBS [id]                  -> User Request Bus Stop\n"
"UCSR [id]                  -> User Request Schedule\n"
"UCAT [bus_id bus_stop_id]  -> User Request Check Bus Arrive Time\n\n"

"-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n"
"# "
*/

#include <iostream>
#include <string.h>
#include <sstream>
#include <thread>
#include <vector>

#include "CCommands.h"
#include "CGenerateRoute.h"
#include "CBus.h"
using namespace std;

// cmd
typedef enum {ERROR = 0, ADBU, ADBS, EBID, EBDR, EBRM, ESID, 
                         ESRM, URBS, UCSR, UCAT, INIT} cmd;


// Main System Operations:
void addBus(string param);
void addBusStop(string param);
void edBusId(string param);
void edBusDefaultRoute(string param);
void edBusRemove(string param);
void edBusStopId(string param);
void edBusStopRemove(string param);

// User Web Busit Operations:
void requestBusStop(string param);
void requestScheduler(string param);
void requestArriveTime(string param);

// Array of thread operations:
void (*operation[10])(string param) = {addBus, addBusStop, edBusId, edBusDefaultRoute, 
                                        edBusRemove, edBusStopId, edBusStopRemove, requestBusStop, 
                                        requestScheduler, requestArriveTime};

// global classes:
    
    // MAP
    #define MAP_DEFAULT_NAME "map_1"
    static CMap map(1);

    // Bus Stop                          id = 1  id = 2   id = 3   id = 4
    const SCoord default_bst_pos[4]  = { {1,15}, {26,13}, {14,17}, {5,1} };
   
    vector<CBusStop> busStopList;

    // Bus Stop
    vector<CBus> busList;


// ==============================================================================================
// ==============================================================================================

// ==============================================================================================
// ==============================================================================================

/**
 *       Private Functions:
*/
// =============================================================================================

// ---___---___---___---___---___---___---___---___---___---___---___---___---___---___---___---
/**
 * Operations cmd functions:
*/
// ---___---___---___---___---___---___---___---___---___---___---___---___---___---___---___---

// add bus
void addBus(string param){
    bool error_flag = false;
    stringstream p;  // get the parameters
    p << param;
    
    /*ID Validation*/
    uint16_t id;
    p >> id;
    if(busList.size() != 0)
    {
        for(int i = 0; i < busList.size(); i++)
        {
            if(busList.at(i).getBusID() == id) //checks if ID already exists
            {
                error_flag = true;
                cout << "ID already exists!\n";
                break;
            }    
        }
    }

    /*Stops Validation*/
    int aux = 0;
    SCoord coord_temp;
    vector <int> stops_list;
    bool status = false;
    while (!p.eof() && ~error_flag)
    {
        status = false;
        if(aux == 0)
			{
				p >> coord_temp.x; // gets the first coord element
				aux = 1;
			}
			else if(aux == 1)
			{
                p >> coord_temp.y; // gets the second coord element
                for(int i = 0; i < busStopList.size(); i++)
                {
                    SCoord busStopPos = busStopList.at(i).getPos();
                    if(busStopPos.x == coord_temp.x && //checks if the Bus Stop coord
                         busStopPos.y == coord_temp.y) // already exists 
                    {
                        status = true;
                        stops_list.push_back(i);
                        //cout << "stops list: " << i << endl;
                        break;
                    }
                }
                  
				aux = 0;
			}
    }
    if(error_flag){
        //return false;
    }
    else if(status)
    {
        busList.push_back({id, EBus::normal_bus}); //pushes back the new Bus
        CBus lastBus = busList.back();
        cout << "Bus ID: " << lastBus.getBusID() << endl 
              << "Bus Type: " << ((lastBus.getBusType() == EBus::normal_bus) ? 
              "normal bus" : "small bus") << endl;
        for(int i = 0; i < stops_list.size(); i++)     //inserts each bus stop in its route
        {
            CBusStop tempBusStop = busStopList.at(stops_list.at(i)); 
            if(lastBus.insertBusStop(tempBusStop))
            {
                cout << "Bus Stop " << (i+1) << " Info: " << endl 
                << "ID: "  << tempBusStop.getID() << endl
                << "Pos: " << "(" << tempBusStop.getPos().x
                << ", "    << tempBusStop.getPos().y << ")" << endl;
            }
            else
                cout << "Error inserting Bus Stop!" << endl;
        }   
        //return true;
    }
    else{
        cout << "Error! Invalid Coordinates!\n";
        //return false;
    }
}
// ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...
// add bus stop
void addBusStop(string param){
    bool error_flag = false;
    stringstream p;  // get the parameters
    p << param;
    
    /*ID Validation*/
    uint16_t id;
    p >> id;
    if(busStopList.size() != 0)
    {
        for(int i = 0; i < busStopList.size(); i++)
        {
            if(busStopList.at(i).getID() == id) //checks if ID already exists
            {
                error_flag = true;
                cout << "ID already exists!\n";
                break;
            }    
        }
    }

    /*Stop Validation*/
    SCoord coord_temp;
    if (~error_flag)
    {
        
        p >> coord_temp.x; // gets the first coord element
        p >> coord_temp.y; // gets the second coord element
        for(int i = 0; i < busStopList.size(); i++)
        {
            SCoord busStopPos = busStopList.at(i).getPos();
            if(busStopPos.x == coord_temp.x && //checks if the Bus Stop coord
                    busStopPos.y == coord_temp.y) // already exists 
            {
                cout << "Bus Stop already exists!\n";
                error_flag = true;
                break;
            }
        }
	}
    if(error_flag){
        //return false; 
    }                     //  |---------CBusStop---------|
    else{                 //   |-----Node-----------| 
        busStopList.push_back({{id, 0x40, coord_temp}, id});
        CBusStop tempBusStop = busStopList.back(); 
        cout << "Bus Stop "  << " Info: " << endl 
                << "ID: "  << tempBusStop.getID() << endl
                << "Pos: " << "(" << tempBusStop.getPos().x
                << ", "    << tempBusStop.getPos().y << ")" << endl;
        //return true;
    }
}

// ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...
// change bus id
void edBusId(string param){
    bool error_flag = true;
    stringstream p;  // get the parameters
    p << param;
    
    /*ID Validation*/
    uint16_t id;
    uint16_t newId;
    int index = 0;
    p >> id;
    p >> newId;
    if(id == newId)
    {
        error_flag = true;
        cout << "Id and new Id are the same!\n";
        return;
        //return false;
    }
    if(busList.size() != 0)
    {
        for(int i = 0; i < busList.size(); i++)
        {
            if(busList.at(i).getBusID() == id) //checks if ID already exists
            {
                error_flag = false;
                index = i;
            } 
            if(busList.at(i).getBusID() == newId)
            {
                error_flag = true;
                cout << "New ID already exists!\n";
                break;
            }
        }
    }
    else
    {
        error_flag = true;
        cout << "There are no Buses in the list!\n";
    }

    if(error_flag){
        cout << "Invalid ID!\n";
        //return false;
    }
    else
    {
        busList.at(index).setBusId(newId);
        cout << "New Id: " << newId << endl;
        //return true;
    }
}

// ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...
// change bus default route
void edBusDefaultRoute(string param){
    bool error_flag = true;
    stringstream p;  // get the parameters
    p << param;
    
    /*ID Validation*/
    int index = 0;
    uint16_t id;
    p >> id;
    if(busList.size() != 0)
    {
        for(int i = 0; i < busList.size(); i++)
        {
            if(busList.at(i).getBusID() == id) //checks if ID already exists
            {
                error_flag = false;
                index = i;
                break;
            }    
        }
    }

    /*Stops Validation*/
    int aux = 0;
    SCoord coord_temp;
    vector <int> stops_list;
    bool status = false;
    while (!p.eof() && ~error_flag)
    {
        status = false;
        if(aux == 0)
			{
				p >> coord_temp.x; // gets the first coord element
				aux = 1;
			}
			else if(aux == 1)
			{
                p >> coord_temp.y; // gets the second coord element
                for(int i = 0; i < busStopList.size(); i++)
                {
                    SCoord busStopPos = busStopList.at(i).getPos();
                    if(busStopPos.x == coord_temp.x && //checks if the Bus Stop coord
                         busStopPos.y == coord_temp.y) // already exists 
                    {
                        status = true;
                        stops_list.push_back(i);
                        break;
                    }
                }
                  
				aux = 0;
			}
    }
    if(error_flag){
        cout << "Bus does not exist!\n";
        //return false;
    }
    else if(status)
    {
        busList.at(index).clearBusStopsList();
        for(int i = 0; i < stops_list.size(); i++) //inserts each bus stop in its route
        {
            CBusStop tempBusStop = busStopList.at(stops_list.at(i));
            busList.at(index).insertBusStop(tempBusStop);
            cout << "Bus Stop " << (i+1) << " Info: " << endl
            << "ID: "  << tempBusStop.getID() << endl
            << "Pos: " << "(" << tempBusStop.getPos().x
            << ", "    << tempBusStop.getPos().y << ")" << endl;
        
        }    
        
        //return true;
    }
    else{
        cout << "Error inserting Bus Stop!" << endl;
        //return false;
    }
}

// ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...
// remove bus
void edBusRemove(string param){
    bool error_flag = true;
    stringstream p;  // get the parameters
    p << param;
    
    /*ID Validation*/
    int index = 0;
    uint16_t id;
    p >> id;
    if(busList.size() != 0)
    {
        for(int i = 0; i < busList.size(); i++)
        {
            if(busList.at(i).getBusID() == id) //checks if ID already exists
            {
                error_flag = false;
                index = i;
                break;
            }    
        }
    }

    if(error_flag){
        cout << "Bus does not exist!\n";
        //return false;
    }
    else
    {
        busList.erase(busList.begin() + index);        
        //return true;
    }
}

// ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...
// change bus stop id
void edBusStopId(string param){
    bool error_flag = true;
    stringstream p;  // get the parameters
    p << param;
    
    /*ID Validation*/
    uint16_t id;
    uint16_t newId;
    int index = 0;
    p >> id;
    p >> newId;
    if(id == newId)
    {
        error_flag = true;
        cout << "Id and new Id are the same!\n";
        return;
        //return false;
    }

    if(busStopList.size() != 0)
    {
        for(int i = 0; i < busStopList.size(); i++)
        {
            if(busStopList.at(i).getID() == id) //checks if ID already exists
            {
                error_flag = false;
                index = i;
            } 
            if(busStopList.at(i).getID() == newId)
            {
                error_flag = true;
                cout << "New ID already exists!\n";
                break;
            }
        }
    }
    else
    {
        error_flag = true;
        cout << "There are no Buses in the list!\n";
    }

    if(error_flag){
        cout << "Invalid ID!\n";
        //return false;
    }
    else
    {
        busStopList.at(index).setID(newId);
        cout << "New Id: " << newId << endl;
        //return true;
    }
}

// ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...
// remove bus stop
void edBusStopRemove(string param){
    bool error_flag = true;
    stringstream p;  // get the parameters
    p << param;
    
    /*ID Validation*/
    int index = 0;
    uint16_t id;
    p >> id;
    if(busStopList.size() != 0)
    {
        for(int i = 0; i < busStopList.size(); i++)
        {
            if(busStopList.at(i).getID() == id) //checks if ID already exists
            {
                error_flag = false;
                index = i;
                break;
            }    
        }
    }

    if(error_flag){
        cout << "Bus Stop does not exist!\n";
        //return false;
    }
    else
    {
        busStopList.erase(busStopList.begin() + index);        
        //return true;
    }
}

// - - - - - - - - - -    - - - - - - - - - -    - - - - - - - - - -    - - - - - - - - - -
// User Web Busit Operations:

// Request bus stop
void requestBusStop(string param){
    stringstream p;  // get the parameters
    p << param;
}

// ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...
// Request Bus Scheduler
void requestScheduler(string param){
    stringstream p;  // get the parameters
    p << param;
}

// ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...
// Request Bus Arrive Time
void requestArriveTime(string param){
    stringstream p;  // get the parameters
    p << param;
}


// ==============================================================================================

// ---___---___---___---___---___---___---___---___---___---___---___---___---___---___---___---
/**
 * Decode cmd functions:
*/
// ---___---___---___---___---___---___---___---___---___---___---___---___---___---___---___---


bool getCmd(string scmd, cmd &_cmd){
    _cmd = ERROR;
    if     ( (scmd == "ADBU") || (scmd == "adbu") )    _cmd = ADBU;
    else if( (scmd == "ADBS") || (scmd == "adbs") )    _cmd = ADBS;
    else if( (scmd == "EBID") || (scmd == "ebid") )    _cmd = EBID;
    else if( (scmd == "EBDR") || (scmd == "ebdr") )    _cmd = EBDR;
    else if( (scmd == "EBRM") || (scmd == "ebrm") )    _cmd = EBRM;
    else if( (scmd == "ESID") || (scmd == "esid") )    _cmd = ESID;
    else if( (scmd == "ESRM") || (scmd == "esrm") )    _cmd = ESRM;
    else if( (scmd == "URBS") || (scmd == "urbs") )    _cmd = URBS;
    else if( (scmd == "UCSR") || (scmd == "ucsr") )    _cmd = UCSR;
    else if( (scmd == "UCAT") || (scmd == "ucat") )    _cmd = UCAT;
    if (_cmd == ERROR)
        return false;
    return true;
}

// ==============================================================================================

bool conditionParam(unsigned short int num_param, cmd &_cmd){
    bool flag = false;
    cout << "num_param = " << num_param  << "  ;  cmd = " << _cmd << endl;
    if ( (_cmd == ADBU || _cmd == EBDR ) && num_param > 4 && (num_param % 2) == 1 )
        flag = true;
    if ( _cmd == ADBS  && num_param == 3 )
        flag = true;
    if ( (_cmd == UCAT || _cmd == EBID || _cmd == ESID) && num_param == 2 )
        flag = true;
    if ( num_param == 1 || _cmd == EBRM || _cmd == ESRM || _cmd == URBS || _cmd == UCSR )
        flag = true;
        cout << "flag = " << flag;
    return flag;
}
// ==============================================================================================

string getParameters(string buffer, cmd &_cmd){

    stringstream ss;     
    unsigned short int num_param = 0;
    bool flag_err = false;

    buffer.erase(0, 5); // erase the cmd 
    ss << buffer;       // saves the rest

    while (!ss.eof() && !flag_err){
        string stemp;
        ss >> stemp; // gets the number in string

        // checks if its a number:
        for (size_t i = 0 ; i < stemp.size() ; i++){
            if (stemp[i] < '0' || stemp[i] > '9'){
                flag_err = true;
                break;
            }
        } 
            num_param++; 
    }
    if(!flag_err && conditionParam(num_param, _cmd)){
        return buffer;
    }else {
        return "!";
    }

}


// ==============================================================================================
// ==============================================================================================
/**
 *       Extern Functions:
*/
// ==============================================================================================
// ==============================================================================================

bool initCmd(){

    // input map
    if (map.inputMap(MAP_DEFAULT_NAME) == false) {
        cout << "ERROR creating the input"<< endl;
        return false;
    }
    //********prints map****************
    // for(int i = 0; i < 27; i++)
    // {
    //     for(int j = 0; j < 27; j++)
    //     {
    //         CNode n;
    //         map.getMapNode(j,i,n);
    //         cout << n.getId() << " ";
    //     }
    //     cout << endl;
    // }

    // add the default bus stops:
    for (int i = 0 ; i < 4 ; i++){
        CNode pno;

        if (map.getMapNode(default_bst_pos[i], pno)){
            busStopList.push_back({pno, (uint16_t)(i+1)});
            //********prints bus stops*******
            // cout << "Pos: " << "(" << busStopList.at(i).getPos().x
            // << ", "    << busStopList.at(i).getPos().y << ")" << endl;
        }
        else {return false;}
    }

    return true;
    
}

// ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...


bool inputCmd( const char* buffer){

    stringstream ss;
    string s = (char*)buffer;

    cmd _cmd = ERROR;
    
    // get command
    if(s.size() > 4){ 

        string scmd = {s[0], s[1], s[2], s[3]}; // get the cmd in string

        if (getCmd(scmd, _cmd)){
            // set parameters 
            s = getParameters(s, _cmd);
            if(s == "!")
                _cmd = ERROR;
            cout << "\ns = " << s <<endl;
        }
    }


    // call thread to execute:
    if (_cmd != ERROR)
    {
        operation[_cmd - 1](s);
        // thread tOp( operation[_cmd], s );  // thread
        //tOp.detach();
        return true;                      // abandon child thread      
    }
    else
        return false;   //  activate the PERROR
    
}



// =========================================================================================
/**
 * Test main func:
 * note: change the return of inputCmd as a string
*/
/*
int main (){
    const char* buffr = "UCSR 12 ";
    const unsigned char * c = (const unsigned char *)buffr;
    string s = inputCmd(c);
    
    cout << s << endl;
    
}*/