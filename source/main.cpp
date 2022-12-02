#include "CPoint.h"
#include "CNode.h"
#include "CBusStop.h"
#include "CRoute.h"
#include "CMap.h"
#include <vector>
#include <iostream>

using namespace std;

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
 */    //================================================

     //TODO================CRoute test=======================
     //================================================
     
     vector <CNode> vn;
     CRoute r(1);

     CNode n1(1,8,0,0);
     CNode n2(2,6,4,3);
     CNode n3(3,12,1,2);

     r.addNode(n1);
     r.addNode(n2);
     r.insertNode(n3, 1);
     vn.push_back( r.getNode(0));
     vn.push_back( r.getNode(1));
     vn.push_back( r.getNode(2));
     r.removeNode(1);
     vn.push_back( r.getNode(1));
     cout << " route[0].byteInfo =  "<< vn[0].getNodeInfo() << endl;
     cout << " route[1].byteInfo =  "<< vn[1].getNodeInfo() << endl;
     cout << " route[2].byteInfo =  "<< vn[2].getNodeInfo() << endl;
     cout << " remove route[1], now :\nroute[1].byteInfo =  "<< vn[3].getNodeInfo() << endl;
     cout << "route info:\n total gain = " << r.getTotalGain()<< "\ntotal time = " << r.getRouteTime() << endl;
     //================================================

    return 0;
}
