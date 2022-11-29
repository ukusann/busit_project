//#include "CPoint.h"
#include "CNode.h"
#include <iostream>
#include "CMap.h"
using namespace std;

int main()
{
     //TODO================CPoint test======================
     //================================================= 
     
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
     
     //================================================= 

     //TODO================CNode test=======================
     //================================================= 
     //*----------------Init variable--------------------
  /*   CPoint p(2,2);
     SCoord s{0, 0};
     SCoord s2{2, 1};
     CNode n(1, 4, 0, s);        // byte -> 0000 0100
     CNode n2(2, 133, 0, s2);    // byte -> 1000 0101 
     //-------------------------------------------------

     //*----------------Get Node Info--------------------
     cout << "Node 1 Byte info: " << (unsigned)n.get_node_info() << endl;
     cout << "Node 2 Byte info: " << (unsigned)n2.get_node_info() << endl;
     //-------------------------------------------------

     //*----------------Set Node Info--------------------
     n.set_node_info(5);
     cout << "Node 1 new Byte info: " << (unsigned)n.get_node_info() << endl;
     //-------------------------------------------------

     //*----------------Is Open--------------------------
     if(n.is_open() == true)
          cout << "Node 1 is open. " << endl;
     else
          cout << "Node 1 is not open. " << endl;

     if(n2.is_open() == true)
          cout << "Node 2 is open. " << endl;
     else
          cout << "Node 2 is not open. " << endl;
     //*-------------------------------------------------

     //*----------------Get Direction--------------------
     cout << "Node 1 distance to goal: " << n.get_direction(p) << endl;
     //-------------------------------------------------

     //*----------------Get Gain-------------------------
     cout << "Node 2 current gain: " << n2.get_gain() << endl;
     //-------------------------------------------------

     //*----------------Set Gain-------------------------
     n2.set_gain(2);
     cout << "Node 2 new gain: " << n2.get_gain() << endl;
     //-------------------------------------------------
     //================================================= 
*/
     //TODO================CMap test=======================
     //================================================
     /*
      CMap map(1);
     
      if (map.inputMap("map_1") == false) 
          cout << "ERROR creating the input"<< endl;
     */
     //================================================

     //TODO================list test=======================
     //================================================
   /*  
   list<int> l{1,2,3,4};
   list<int> l1{5,6,7,8};
   list<list<int>> ll;
   ll.push_back(l);
   ll.push_back(l1);

   list<list<int>>::iterator itr = ll.begin();

   list<int>::iterator it = itr->begin();
   itr->insert(it, 88);
   itr->insert(it, 89);

   itr++;
   it = itr->begin();
   itr->insert(it, 98);
   itr->insert(it, 99);


   for (itr=ll.begin(); itr != ll.end(); itr++)
   {
       list<int>tl=*itr;

       for (it=tl.begin(); it != tl.end(); it++)
       {
           cout<<*it;
       }
       cout<<endl<<"End"<<endl;
   }      
*/
    return 0;
}
