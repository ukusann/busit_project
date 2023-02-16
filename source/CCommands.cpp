
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
#include <sstream>
#include <thread>
#include <vector>
#include <mqueue.h>
#include <unistd.h>
#include <string.h>

#include "CCommands.h"
#include "CGenerateRoute.h"
#include "CBus.h"
using namespace std;

//Message Queue:
#define MSG_QUEUE_NAME  "/errorMsg"
#define MSG_QUEUE_MAX_LEN 10000

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
     string err_msg;
     stringstream p;  // get the parameters
     int id;
     vector<CRoute> multir;   // Bus routes
     vector<CBusStop> busSt;  // Bus's list of bus stops
     vector<SCoord> pos;      // Input positions
     p << param;              // Set the parameters
     vector<CNode> vnode;     // Routes beguin and end nodes

     // Get the param:
     p >> id;
     while (!p.eof()){
          unsigned short int x,y;
          p >> x >> y;
          pos.push_back({x,y});
     }

     // See if the Bus Stops exists:
     for(int i = 0; i < pos.size() ;i++){
          if (map.mapIsBusStop(pos.at(i))){   // test  if is a bus stop
               CNode temp_n;
               map.getMapNode(pos.at(i), temp_n);
               vnode.push_back(temp_n);           // Saves the node               
          }
          else {
               error_flag = true;
               err_msg = "ERROR: No Bus Stop on the default Bus Route";
               break;
          }
     }

     // Generate a multi-route:
     if (!error_flag){
          CRoute r(id);
          CGenerateRoute gr(&map, &r);       // sets the map
          multir = gr.multRoutes(vnode);     // generate the route
          if(multir.empty()){                // teste if a route was generated 
               error_flag = true;
               err_msg    = "ERROR: Can't generate a route ";
          }
     }
     // Saves and sets the Bus:
     if (!error_flag){
          CBus bus (id, EBus::normal_bus);   // Creates a Bus
          bus.setRoutes(multir);             // Set the routes
          for(int i = 0 ; i < vnode.size() ; i++){ // Set the bus list of bus stops
               for(int j = 0 ; j < busStopList.size() ; j++){
                    if (vnode[i].getId() == busStopList[j].getBSnodeId())   
                         bus.insertBusStop(busStopList[j]);                
               }               
          }
          busList.push_back(bus);            // Saves the bus         
     }
     if (error_flag)
          cout << err_msg << endl;
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
        cout << "A bus will pick you up soon!\n";   
        //return true;
    }
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

     // add the default bus stops:
     for (int i = 0 ; i < 4 ; i++){
          CNode pno;

          if (map.getMapNode(default_bst_pos[i], pno)){
               
               busStopList.push_back({pno, (uint16_t)(i+1)});
               map.mapBusStop(default_bst_pos[i], true);
          }
          else {return false;}
     }
     cout << map.printMap();

    return true;
    
}

// ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...


bool inputCmd(future<string> &buffer){

    stringstream ss;
    string s = buffer.get();

    cmd _cmd = ERROR;

    mqd_t msgq_id;
    unsigned int msgprio = 1;
    pid_t my_pid = getpid();
    char msgcontent[MSG_QUEUE_MAX_LEN];

    msgq_id = mq_open(MSG_QUEUE_NAME, O_CREAT | O_RDWR, 0666, NULL); // opens an existing message queue to read

    /* checks if message queue could be opened*/
    if (msgq_id == (mqd_t)-1) 
    {
        perror("In mq_open()");
        exit(1);
    }

    snprintf(msgcontent, MSG_QUEUE_MAX_LEN, "Hello from process PUT.");
   

    if(mq_send(msgq_id, msgcontent, strlen(msgcontent)+1, msgprio) == -1)
        perror("In mq_send()");
    /* closing the queue        -- mq_close() */
    mq_close(msgq_id); 

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
       // operation[_cmd - 1](s);
        thread execute_cmd(operation[_cmd - 1], (s)); // launch the thread
        execute_cmd.detach();                         // run the thread apart from this thread
        return true;                    
    }
    else
        return false;   //  activate the PERROR
    
}

// =========================================================================================
