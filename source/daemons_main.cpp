#include "CDaemons.h"
#include <stdexcept>
#include <iostream>

using namespace std;

int main()
{
	try
	{
		CDaemons d;
		d.idle();
	}

	catch(invalid_argument &e)
	{
		cerr << e.what() << endl;
        return -1;
	}

	catch(length_error &e)
	{
		cerr << e.what() << endl;
        return -1;
	}

	catch(runtime_error &e)
	{
		cerr << e.what() << endl;
        return -1;
	}

	return 0;
}