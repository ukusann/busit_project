//#include "CPoint.h"
//#include "CNode.h"
#include "CBusStop.h"
#include <iostream>
#include <string>

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
     cout << "distance: " << p.get_distance(p2) << endl;
     cout << "distance: " << p.get_distance(c) << endl;
     //-------------------------------------------------

    //*----------------Get point test--------------------
     SCoord c2 = p.get_point();
     cout << "initial point:\n" << "x = " << c2.x
          << endl << "y = " << c2.y << endl;
     //--------------------------------------------------

     //*----------------Set point test--------------------
     p.set_point(c);
     cout << "new point position:\n" << "x = " << p.get_point().x
          << endl << "y = " << p.get_point().y << endl;

     p.set_point(p2);
     cout << "new point position:\n" << "x = " << p.get_point().x
          << endl << "y = " << p.get_point().y << endl;
     //--------------------------------------------------
     */
     //================================================= 

     //TODO:================CNode test=======================
     //================================================= 
     /*
     //*----------------Init variable--------------------
     CPoint p(2,2);
     SCoord s{0, 0};
     SCoord s2{2, 1};
     CNode n(1, 4, 0, s);        // byte -> 0000 0100
     CNode n2(2, 133, 0, s2);    // byte -> 1000 0101 
     //-------------------------------------------------

     //*----------------Get Node Info--------------------
     cout << "Node 1 Byte info: " << (unsigned)n.getNodeInfo() << endl;
     cout << "Node 2 Byte info: " << (unsigned)n2.getNodeInfo() << endl;
     //-------------------------------------------------

     //*----------------Set Node Info--------------------
     n.setNodeInfo(5);
     cout << "Node 1 new Byte info: " << (unsigned)n.getNodeInfo() << endl;
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
     //-------------------------------------------------

     //*----------------Get Direction--------------------
     cout << "Node 1 distance to goal: " << n.getDirection(p) << endl;
     //-------------------------------------------------

     //*----------------Get Gain-------------------------
     cout << "Node 2 current gain: " << n2.getGain() << endl;
     //-------------------------------------------------

     //*----------------Set Gain-------------------------
     n2.setGain(2);
     cout << "Node 2 new gain: " << n2.getGain() << endl;

     //-------------------------------------------------
     */
     //================================================= 

     //TODO================CBusStop test======================
     //================================================= 
     /*
     //*----------------Init variable--------------------
     CPoint p(1,1);
     CPoint p2(1,2);
     SCoord c{1, 3};
     string str = "av. liberdade";
     CBusStop bs(str, p, 1);
     //-------------------------------------------------

     //*----------------Get ID test---------------------
     cout << "Bus Stop ID: " << bs.getID() << endl;
     //-------------------------------------------------

     //*----------------Get pos test---------------------
     SCoord c2 = bs.getPos().getPoint();
     cout << "Bus Stop pos:\n" << "x = " << c2.x 
          << endl << "y = " << c2.y << endl;
     //--------------------------------------------------

     //*----------------Get name test--------------------
     cout << "Bus Stop name: " << bs.getName() << endl;
     //--------------------------------------------------
     */
     //================================================= 

     
     return 0;
}
