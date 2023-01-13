// #include "CPoint.h"
// #include "CNode.h"
// #include "CBusStop.h"
// #include "CRoute.h"
// #include "CMap.h"
#include "CGenerateRoute.h"

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

// vector::at
#include <iostream>
#include <vector>

using namespace std;

void getVector(unsigned ind, int &r){
    vector<vector<int>> *v;
    vector<vector<int>> a;
    v = &a;
    vector<int> myvector (10);   // 10 zero-initialized ints

      // assign some values:
    for (unsigned i=0; i<myvector.size(); i++)
        myvector.at(i)=i;
    v->push_back(myvector);
    r = v->at(0).at(ind);
    cout << "my number is:" << r << endl;
    return;  
    }

int main ()
{
    int a = 0;
    int *r = &a;
    getVector(2,*r);
    
  cout << "my number is:" << *r << endl;
  

  return 0;
}



     CMap map(1);
     CRoute r(1);

     CNode *i_n;
     CNode *f_n;


     
     if (map.inputMap("map_1") == false) 
          cout << "ERROR creating the input"<< endl;
     cout << "IN" << endl << endl;

     map.getMapNode(0, 0, *i_n);
     map.getMapNode(8, 2, *f_n);
     cout << "out" << endl << endl;
     
     cout << "begin node"<< i_n->getNodeInfo() <<endl;
     cout << "end node"  << f_n->getNodeInfo() <<endl;
          
     CGenerateRoute gr(&map, &r);     

     CRoute r2 = gr.simpleRoute(*i_n, *f_n, 2);
     cout << "Route 2 ID: " << r2.getRouteID() << endl;
     cout << "Route 2 total gain: " << r2.getTotalGain() << endl;
     cout << "Route 2 Time: " << r2.getRouteTime() << endl;
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

     //kill(pid2, SIGTERM);

     kill(pid, SIGTERM);
*/
     //================================================

    return 0;
}
