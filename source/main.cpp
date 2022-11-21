#include "CPoint.h"
#include <iostream>

using namespace std;

int main()
{
    //----------------Init variable--------------------
    CPoint p(1,1);
    CPoint p2(1,2);
    SCoord c{1, 3};
    //-------------------------------------------------a

    //----------------Distance test--------------------
    cout << "distance: " << p.get_distance(p2) << endl;
    cout << "distance: " << p.get_distance(c) << endl;
    //-------------------------------------------------

    //----------------Get point test--------------------
    SCoord c2 = p.get_point();
    cout << "initial point:\n" << "x = " << c2.x
         << endl << "y = " << c2.y << endl;
    //--------------------------------------------------

    //----------------Set point test--------------------
    p.set_point(c);
    cout << "new point position:\n" << "x = " << p.get_point().x
         << endl << "y = " << p.get_point().y << endl;

    p.set_point(p2);
    cout << "new point position:\n" << "x = " << p.get_point().x
         << endl << "y = " << p.get_point().y << endl;
    //--------------------------------------------------
    return 0;
}
