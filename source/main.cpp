// #include "CPoint.h"
// #include "CNode.h"
// #include "CBusStop.h"
// #include "CRoute.h"
// #include "CMap.h"
//#include "CGenerateRoute.h"
#include "CCommands.h"

#include <vector>
#include <iostream>
#include <signal.h>
#include <sys/syslog.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> 
#include <cstdlib>



using namespace std;

void signal_handler(int sig) {
	switch(sig) {
		case SIGHUP:
			syslog(LOG_INFO,"Hangup signal catched");
			break;

          case SIGUSR1:
            syslog(LOG_INFO,"User signal catched");
            break;

		case SIGTERM:
			syslog(LOG_INFO,"Terminate signal catched");
			exit(0);
			break;
	}
}

int main()
{
     //TODO================CPoint test======================
     //================================================= 
     /*
     //*----------------Init variable--------------------
     CPoint p(1,1);
     CPoint p2(1,2);
     SCoord c{1, 3};
     //-------------------------------------------------

     //*----------------Distance test--------------------
     cout << "distance: " << p.getDistance(p2) << endl;
     cout << "distance: " << p.getDistance(c) << endl;
     //-------------------------------------------------

    //*----------------Get point test--------------------
     SCoord c2 = p.getPoint();
     cout << "initial point:\n" << "x = " << c2.x
          << endl << "y = " << c2.y << endl;
     //--------------------------------------------------

     //*----------------Set point test--------------------
     p.setPoint(c);
     cout << "new point position:\n" << "x = " << p.getPoint().x
          << endl << "y = " << p.getPoint().y << endl;

     p.setPoint(p2);
     cout << "new point position:\n" << "x = " << p.getPoint().x
          << endl << "y = " << p.getPoint().y << endl;
     //--------------------------------------------------
     */
     //================================================= 

     //TODO================CNode test=======================
     //================================================= 
     /*
     //*----------------Init variable--------------------
     CPoint p(2,2);
     SCoord s{0, 0};
     SCoord s2{2, 1};
     CNode n(1, 4, 0, 0);     // byte -> 0000 0100
     CNode n2(2, 133, s2);    // byte -> 1000 0101 
     //-------------------------------------------------
     /*
     //*----------------Get Node Info--------------------
     cout << "Node 1 Byte info: " << n.getNodeInfo() << endl;
     cout << "Node 2 Byte info: " << n2.getNodeInfo() << endl;
     //-------------------------------------------------

     //*----------------Set Node Info--------------------
     n.setNodeInfo(5);
     cout << "Node 1 new Byte info: " << n.getNodeInfo() << endl;
     //-------------------------------------------------

     //*----------------Is Open--------------------------
     if(n.isOpen() == true)
          cout << "Node 1 is open. " << endl;
     else
          cout << "Node 1 is not open. " << endl;

     if(n2.isOpen() == true)
          cout << "Node 2 is open. " << endl;
     else
          cout << "Node 2 is not open. " << endl;
     //*-------------------------------------------------

     //*----------------Get Direction--------------------
     cout << "Node 1 distance to goal: " << n.getDirection(p) << endl;
     //-------------------------------------------------

     //*----------------Get Gain-------------------------
     cout << "Node 2 current gain: " << n2.getGain() << endl;
     //-------------------------------------------------

     //*----------------Set Gain-------------------------
     n2.setGain(2);
     cout << "Node 2 new gain: " << n2.getGain() << endl;
     */
     //-------------------------------------------------
     //================================================= 

     //TODO================CBusStop test====================
     //================================================
     /*
     CPoint pnt(1,1);
     CBusStop bs("Av. Liberdade", pnt, 1);
     bs.updateDisplay();
     */
     //================================================

     //TODO================CMap test=======================
     //================================================
/*     
     CMap map(1);

     if (map.inputMap("map_1") == false) 
          cout << "ERROR creating the input"<< endl;
     //================================================
*/
     //TODO================CRoute test=======================
     //================================================
/*     
     vector <CNode> vn;
     CRoute r(1);

     CNode n1(1,8,0,0);
     CNode n2(2,6,4,3);
     CNode n3(3,12,1,2);
     //CNode n4 = r.getNode(4);

     cout << "Route ID: " << r.getRouteID() << endl;
     cout << "Route total gain: " << r.getTotalGain() << endl;
     cout << "Route Time: " << r.getRouteTime() << endl;
     //cout << "Route Pos: " << r.getRoutePos(0) << endl;
     //================================================
*/
     //TODO================CGenerateRoute test=======================
     //================================================

/*
     SCoord bus_st_pos[4] = { {1,15}, {26,13}, {14,17}, {5,1} };
     CMap map(1);
     CRoute r(1);

     CNode *i_n = new CNode;
     CNode *f_n = new CNode;
     CNode *pnodet = new CNode;
     

     
     if (map.inputMap("map_1") == false) 
          cout << "ERROR creating the input"<< endl;

     for (int i = 0; i < 27; i++)
    {
        for(int j = 0; j < 27; j++){
          map.getMapNode(j, i, *pnodet);
          int c = pnodet->getId();
            if (c < 10)
                cout << "  " << c++ << " ";
            else if (c < 100)
                cout << " " << c++ << " ";
            else 
                cout << c++ << " ";
            
        }
        cout << endl;
    }

     cout << "IN" << endl << endl;
     map.getMapNode(bus_st_pos[1],*i_n);
     map.getMapNode(bus_st_pos[2],*f_n);
          
     CGenerateRoute gr(&map, &r);     
     cout << "out" << endl << endl;

     CRoute r2 = gr.simpleRoute(*i_n, *f_n, 2);
     r2.printRouteAndMem();
     cout << "Route 2 ID: " << r2.getRouteID() << endl;
     cout << "Route 2 total gain: " << r2.getTotalGain() << endl;
     cout << "Route 2 Time: " << r2.getRouteTime() << endl;

// ===============================================================================================
// Multiroute:
     vector<CNode> list_n;

     for(int i = 0 ; i < 4 ; i++ ){
          CNode tempnode;
          map.getMapNode(bus_st_pos[i], tempnode);
          list_n.push_back(tempnode);
          cout << "ID of node" <<tempnode.getId() << endl;
     }
     

     vector<CRoute> multir = gr.multRoutes(list_n);
     cout << "get here!\n\n";
     for(int i = 0 ; i < 3 ; i++ )
          multir[i].printRouteAndMem();
*/  
     //================================================

     //TODO================Daemon test=======================
     //================================================
/*
     pid_t pid;
     signal(SIGUSR1, signal_handler); // Register signal handler
     signal(SIGTERM, signal_handler); // Register signal handler
     pid = getpid();      //Process ID of itself
     printf("Busit PID: %d\n", pid);
     
     int total_length = 1024; 

     char line[total_length];
     FILE * command = popen("pidof -s daemon.elf","r");

     fgets(line,total_length,command);

     pid_t pid2 = strtoul(line,NULL,10);
     pclose(command);
     
     printf("Daemon PID: %d\n", pid2);
     
     kill(pid2, SIGUSR1);        // Send SIGUSR1 to daemon

     kill(pid2, SIGTERM);

     kill(pid, SIGTERM);
*/
     //================================================

     //TODO================CCommands test=======================
     //================================================
     const char *addBus            = "ADBU 2 1 15 26 13";
     const char *addBusStop        = "ADBS 5 1 18";
     const char *editBusID         = "EBID 2 3";
     const char *editBusDefRt      = "EBDR 3 14 17 5 1";
     const char *removeBus         = "EBRM 3";
     const char *editBusStopID     = "ESID 5 9";
     const char *removeBusStop     = "ESRM 9";
     const char *requestBusStop    = "URBS 4"; 
     

     if(initCmd())
     {
          if(inputCmd(addBus))
               cout << "Success!\n";
          else
               cout << "Error in input cmd!\n";

          if(inputCmd(addBusStop))
               cout << "Success!\n";
          else
               cout << "Error in input cmd!\n";

          if(inputCmd(editBusID))
               cout << "Success!\n";
          else
               cout << "Error in input cmd!\n";

          if(inputCmd(editBusDefRt))
               cout << "Success!\n";
          else
               cout << "Error in input cmd!\n";          
                    
          if(inputCmd(removeBus))
               cout << "Success!\n";
          else
               cout << "Error in input cmd!\n";  

          if(inputCmd(editBusStopID))
               cout << "Success!\n";
          else
               cout << "Error in input cmd!\n";    

          if(inputCmd(removeBusStop))
               cout << "Success!\n";
          else
               cout << "Error in input cmd!\n";
          
          if(inputCmd(requestBusStop))
               cout << "Success!\n";
          else
               cout << "Error in input cmd!\n";                           
     }     
     else
          cout << "Error in init cmd!\n";
    return 0;
}
