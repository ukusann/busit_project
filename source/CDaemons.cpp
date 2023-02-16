#include "CDaemons.h"
#include <stdexcept>
#include <unistd.h> 
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <cstring>
#include <iostream>
#include <sstream>

using namespace std;


//===========================================================
//===========================================================
// ***********Beginning of Constructor/Destructor: **********
CDaemons::CDaemons()
{
    setInfo();
}

CDaemons::~CDaemons(){}

// ***********End of Constructor/Destructor: ****************
//===========================================================
//===========================================================
// ***********Beginning of Private Functions: ***************

void CDaemons::setInfo()
{
    this->pid = fork();

    if (this->pid < 0) { // on error exit
		syslog(LOG_ERR, "%s\n", "fork");
        throw invalid_argument("Pid not valid!");
		exit(EXIT_FAILURE);
	}

    if (this->pid > 0){  
		printf("Deamon PID: %d\n", pid);	
		exit(EXIT_SUCCESS); // parent process (exit)
	}

    this->sid = setsid();

    if (sid < 0) { // on error exit
		syslog(LOG_ERR, "%s\n", "setsid");
        throw invalid_argument("Sid not valid!");
		exit(EXIT_FAILURE);
	}

	// make '/' the root directory
	if (chdir("/") < 0) { // on error exit
		syslog(LOG_ERR, "%s\n", "chdir");
        throw invalid_argument("Error making the root directory!");
		exit(EXIT_FAILURE);
	}

    umask(0);

	close(STDIN_FILENO);  // close std input file descriptor
	close(STDOUT_FILENO); // close std output file descriptor
	close(STDERR_FILENO); // close std error file descriptor

}

//-----------------------------------------------------------

void CDaemons::signalHandler(int sig)
{
    switch(sig) {
		case SIGHUP:
			syslog(LOG_INFO,"Hangup signal catched");
			break;

        case SIGUSR1:
            syslog(LOG_INFO,"User signal catched");
			raise(SIGTERM);
            break;

		case SIGTERM:
			syslog(LOG_INFO,"Terminate signal catched");
			exit(0);
			break;
	}
}
// ***********End of Private Functions: *********************
//===========================================================
//===========================================================
// ***********Beginning of Public Functions: ****************
pid_t CDaemons::getPid()
{
	return this->pid;
}


// ***********End of Public Functions: **********************
//===========================================================
//===========================================================
//====================================================
//**************** FastCGI Functions *****************
#ifdef __cplusplus
extern "C" {
#endif

FFUNC init_logger_in_instance() {
	fprintf(stderr, "%s\n", "start instance");
	fprintf(stderr, "%s\n", "init logging");
}



//-----------------------------------------------------

FFUNC busReqCallback(ffunc_session_t * session)
{	
	CServer me;
	char *pmet = ffunc_get_fcgi_param(session, "REQUEST_METHOD");
	string method(pmet);

	char *puri = ffunc_get_fcgi_param(session, "REQUEST_URI");
	string uri(puri);
	
	string query = "";
	if(session->query_str)
	{
		query = string(session->query_str);

		size_t found = uri.find(query);
		uri.erase(found-1, query.length()+1);
	}
	if(uri == "/bus")
		ffunc_write_out(session, me.getAdminForm().c_str());
	else
		ffunc_write_out(session, "%s\n", "Error in URL");

	ffunc_str_t body;
	ffunc_read_body(session, &body); //ready body from actual session
	string line;					
	string intermediate;
	/*admin variables*/
	string admin_name;
	string admin_pass;

	// body process
	getline((istringstream)body.data, line); //get one line from body
	stringstream check(line);
	
	/* process body with structure 'username=XXX&pwd=XXX' */
	while (getline(check, intermediate, '&'))	// Separate the lines by & or end of string
	{	
		int begin_info = 0;
		size_t namePos = intermediate.find("username"); // locate 'username' in body
		if(namePos != string::npos) // checks if 'username' exists
			for(string::iterator it = intermediate.begin() + namePos; it != intermediate.end(); it++)
			{
				if(*it == '=')
					begin_info = 1; // From this char it should record in the string
				else if(begin_info)
					admin_name.push_back(*it); // Append char in the string
			}
		
		size_t passPos = intermediate.find("pwd"); // locate 'pwd' in body
		if(passPos!= string::npos) // checks if 'pwd' exists
			for(string::iterator it = intermediate.begin() + passPos; it != intermediate.end(); it++)
			{
				if(*it == '=')
					begin_info = 1;	// From this char it should record in the string
				else if(begin_info)
					admin_pass.push_back(*it); // Append char in the string
			}
	}
	

	if (method == "POST" && uri == "/bus")
	{
		if(admin_name.compare(ADMIN_NAME) == 0)
			if(admin_pass.compare(ADMIN_PASS) == 0)
				ffunc_write_out(session, me.getBusConfigPage().c_str());
			else
				ffunc_write_out(session, me.getAnswerWrongPass().c_str());
		else
			ffunc_write_out(session, me.getAnswerWrongName().c_str());
	}
}

//-----------------------------------------------------

FFUNC userReqCallback(ffunc_session_t * session) {
	CServer me;
	char *pmet = ffunc_get_fcgi_param(session, "REQUEST_METHOD");
	string method(pmet);

	char *puri = ffunc_get_fcgi_param(session, "REQUEST_URI");
	string uri(puri);
	
	string query = "";
	if(session->query_str)
	{
		query = string(session->query_str);

		size_t found = uri.find(query);
		uri.erase(found-1, query.length()+1);
	}
	if(uri == "/user")
		ffunc_write_out(session, me.getUserPage().c_str());
	else
		ffunc_write_out(session, "%s\n", "Error in URL");
}


//-----------------------------------------------------

FFUNC adminReqCallback(ffunc_session_t * session) {
	CServer me;
	char *pmet = ffunc_get_fcgi_param(session, "REQUEST_METHOD");
	string method(pmet);

	char *puri = ffunc_get_fcgi_param(session, "REQUEST_URI");
	string uri(puri);
	
	string query = "";
	if(session->query_str)
	{
		query = string(session->query_str);

		size_t found = uri.find(query);
		uri.erase(found-1, query.length()+1);
	}
	if(uri == "/admin")
		ffunc_write_out(session, me.getAdminPage().c_str());
	else
		ffunc_write_out(session, "%s\n", "Error in URL");
}

//-----------------------------------------------------

FFUNC ADBUReqCallback(ffunc_session_t * session) {
	CServer me;
	char *pmet = ffunc_get_fcgi_param(session, "REQUEST_METHOD");
	string method(pmet);

	char *puri = ffunc_get_fcgi_param(session, "REQUEST_URI");
	string uri(puri);
	
	string query = "";
	if(session->query_str)
	{
		query = string(session->query_str);

		size_t found = uri.find(query);
		uri.erase(found-1, query.length()+1);
	}
	if(uri == "/ADBU")
		ffunc_write_out(session, me.getADBUpage().c_str());
	else
		ffunc_write_out(session, "%s\n", "Error in URL");

	ffunc_str_t body;
	ffunc_read_body(session, &body); //ready body from actual session
	string line;					
	string intermediate;
	/*admin variables*/
	string busID_str = "";
	string busStops_str = "";

	// body process
	getline((istringstream)body.data, line); //get one line from body
	stringstream check(line);
	
	/* process body with structure 'busId=XXX&stops=X+X+X+X+X' */
	while (getline(check, intermediate, '&'))	// Separate the lines by & or end of string
	{	
		int begin_info = 0;
		size_t IDPos = intermediate.find("busID"); // locate 'busId' in body
		if(IDPos != string::npos) // checks if 'busID' exists
			for(string::iterator it = intermediate.begin() + IDPos; it != intermediate.end(); it++)
			{
				if(*it == '=')
					begin_info = 1; // From this char it should record in the string
				else if(begin_info)
					busID_str.push_back(*it); // Append char in the string
			}
		
		size_t stopsPos = intermediate.find("stops"); // locate 'stops' in body
		if(stopsPos!= string::npos) // checks if 'stops' exists
			for(string::iterator it = intermediate.begin() + stopsPos; it != intermediate.end(); it++)
			{
				if(*it == '=')
					begin_info = 1;	// From this char it should record in the string
				else if(begin_info)
					busStops_str.push_back(*it); // Append char in the string
			}
	}
	// ffunc_write_out(session, "%s\n", busID_str.c_str());
	// ffunc_write_out(session, "%s\n", busStops_str.c_str());
	int busId = 0; 
	vector <int> busStops;
	if(busID_str != "")
		busId = stoi(busID_str);
	
	if(busStops_str != "")
	{
		string tmp;
		for(string::iterator it = busStops_str.begin(); it != busStops_str.end(); it++)
		{
			if(*it != '+')
			{
				tmp.push_back(*it);
			}
			else
			{
				busStops.push_back(stoi(tmp));
				tmp = "";
			}
		}
		busStops.push_back(stoi(tmp));
	}
	
	ffunc_write_out(session, "Bus ID: %d\n", busId);
	if(!busStops.empty())
	{
		int i = 0;
		int aux = 0;
		for(vector<int>::iterator it = busStops.begin(); it != busStops.end(); it++)
		{
			if(aux == 0)
			{
				ffunc_write_out(session, "Bus Stop %d: (%d, ", ++i, *it);
				aux = 1;
			}
			else if(aux == 1)
			{
				ffunc_write_out(session, "%d) ", *it);
				aux = 0;
			}
		}
	}

	if (method == "POST" && uri == "/ADBU")
	{
		if(busId == 1)
			ffunc_write_out(session, me.getADBUwrongID().c_str());
		else if(busStops.size() > 20)
			ffunc_write_out(session, me.getADBUwrongBusStops().c_str());
		else if(busStops.size()%2 != 0)
		{
			ffunc_write_out(session, me.getADBUinvalidBusStops().c_str());
		}
		else if(busId == 0 || busStops.size() == 0)
			ffunc_write_out(session, me.getADBUinvalidNumber().c_str());
	}		
}

//-----------------------------------------------------

FFUNC ADBSReqCallback(ffunc_session_t * session) {
	CServer me;
	char *pmet = ffunc_get_fcgi_param(session, "REQUEST_METHOD");
	string method(pmet);

	char *puri = ffunc_get_fcgi_param(session, "REQUEST_URI");
	string uri(puri);
	
	string query = "";
	if(session->query_str)
	{
		query = string(session->query_str);

		size_t found = uri.find(query);
		uri.erase(found-1, query.length()+1);
	}
	if(uri == "/ADBS")
		ffunc_write_out(session, me.getADBSpage().c_str());
	else
		ffunc_write_out(session, "%s\n", "Error in URL");

	ffunc_str_t body;
	ffunc_read_body(session, &body); //ready body from actual session
	string line;					
	string intermediate;
	/*admin variables*/
	string busID_str = "";
	string busStops_str = "";

	// body process
	getline((istringstream)body.data, line); //get one line from body
	stringstream check(line);

	/* process body with structure 'busStopId=XXX&coord=X+X+X+X+X' */
	while (getline(check, intermediate, '&'))	// Separate the lines by & or end of string
	{	
		int begin_info = 0;
		size_t IDPos = intermediate.find("busStopID"); // locate 'busId' in body
		if(IDPos != string::npos) // checks if 'busID' exists
			for(string::iterator it = intermediate.begin() + IDPos; it != intermediate.end(); it++)
			{
				if(*it == '=')
					begin_info = 1; // From this char it should record in the string
				else if(begin_info)
					busID_str.push_back(*it); // Append char in the string
			}
		
		size_t stopsPos = intermediate.find("coord"); // locate 'stops' in body
		if(stopsPos!= string::npos) // checks if 'stops' exists
			for(string::iterator it = intermediate.begin() + stopsPos; it != intermediate.end(); it++)
			{
				if(*it == '=')
					begin_info = 1;	// From this char it should record in the string
				else if(begin_info)
					busStops_str.push_back(*it); // Append char in the string
			}
	}
	// ffunc_write_out(session, "%s\n", busID_str.c_str());
	// ffunc_write_out(session, "%s\n", busStops_str.c_str());
	int busId = 0; 
	vector <int> busStops;
	if(busID_str != "")
		busId = stoi(busID_str);
	
	if(busStops_str != "")
	{
		string tmp;
		for(string::iterator it = busStops_str.begin(); it != busStops_str.end(); it++)
		{
			if(*it != '+')
			{
				tmp.push_back(*it);
			}
			else
			{
				busStops.push_back(stoi(tmp));
				tmp = "";
			}
		}
		busStops.push_back(stoi(tmp));
	}
	
	ffunc_write_out(session, "Bus Stop ID: %d\n", busId);
	if(!busStops.empty())
	{
		int aux = 0;
		for(vector<int>::iterator it = busStops.begin(); it != busStops.end(); it++)
		{
			if(aux == 0)
			{
				ffunc_write_out(session, "Bus Stop Coord: (%d, ", *it);
				aux = 1;
			}
			else if(aux == 1)
			{
				ffunc_write_out(session, "%d) ", *it);
				aux = 0;
			}
		}
	}

	if (method == "POST" && uri == "/ADBS")
	{
		if(busId == 1)
			ffunc_write_out(session, me.getADBSwrongID().c_str());
		else if(busStops.size() > 2)
			ffunc_write_out(session, me.getADBSinvalidBusStop().c_str());
		else if(busStops.size()%2 != 0)
		{
			ffunc_write_out(session, me.getADBSinvalidBusStop().c_str());
		}
		else if(busId == 0 || busStops.size() == 0)
			ffunc_write_out(session, me.getADBSinvalidNumber().c_str());

	}	
}

//-----------------------------------------------------

FFUNC EBIDReqCallback(ffunc_session_t * session) {
	CServer me;
	char *pmet = ffunc_get_fcgi_param(session, "REQUEST_METHOD");
	string method(pmet);

	char *puri = ffunc_get_fcgi_param(session, "REQUEST_URI");
	string uri(puri);
	
	string query = "";
	if(session->query_str)
	{
		query = string(session->query_str);

		size_t found = uri.find(query);
		uri.erase(found-1, query.length()+1);
	}
	if(uri == "/EBID")
		ffunc_write_out(session, me.getEBIDpage().c_str());
	else
		ffunc_write_out(session, "%s\n", "Error in URL");

	ffunc_str_t body;
	ffunc_read_body(session, &body); //ready body from actual session
	string line;					
	string intermediate;
	/*admin variables*/
	string busID_str = "";
	string newBusID_str = "";

	// body process
	getline((istringstream)body.data, line); //get one line from body
	stringstream check(line);
	
	/* process body with structure 'busID=XXX&newBusID=X+X+X+X+X' */
	while (getline(check, intermediate, '&'))	// Separate the lines by & or end of string
	{	
		int begin_info = 0;
		size_t IDPos = intermediate.find("busID"); // locate 'busID' in body
		if(IDPos != string::npos) // checks if 'busID' exists
			for(string::iterator it = intermediate.begin() + IDPos; it != intermediate.end(); it++)
			{
				if(*it == '=')
					begin_info = 1; // From this char it should record in the string
				else if(begin_info)
					busID_str.push_back(*it); // Append char in the string
			}
		
		size_t newIdPos = intermediate.find("newBusID"); // locate 'newBusID' in body
		if(newIdPos!= string::npos) // checks if 'newBusID' exists
			for(string::iterator it = intermediate.begin() + newIdPos; it != intermediate.end(); it++)
			{
				if(*it == '=')
					begin_info = 1;	// From this char it should record in the string
				else if(begin_info)
					newBusID_str.push_back(*it); // Append char in the string
			}
	}
	// ffunc_write_out(session, "%s\n", busID_str.c_str());
	// ffunc_write_out(session, "%s\n", busStops_str.c_str());
	int busId 		= 0; 
	int newBusId 	= 0;
	if(busID_str != "")
		busId = stoi(busID_str);

	if(newBusID_str != "")
		newBusId = stoi(newBusID_str);
	
	ffunc_write_out(session, "Current ID: %d\n New ID: %d\n", busId, newBusId);
	

	if (method == "POST" && uri == "/EBID")
	{
		if(busId == 1)
			ffunc_write_out(session, me.getEBIDwrongCurID().c_str());
		else if(busId == 0 || newBusId == 0)
			ffunc_write_out(session, me.getEBIDinvalidNumber().c_str());
		else if(newBusId == 2 || newBusId == busId)
			ffunc_write_out(session, me.getEBIDwrongNewID().c_str());
		
	}
}

//-----------------------------------------------------

FFUNC EBDRReqCallback(ffunc_session_t * session) {
		CServer me;
	char *pmet = ffunc_get_fcgi_param(session, "REQUEST_METHOD");
	string method(pmet);

	char *puri = ffunc_get_fcgi_param(session, "REQUEST_URI");
	string uri(puri);
	
	string query = "";
	if(session->query_str)
	{
		query = string(session->query_str);

		size_t found = uri.find(query);
		uri.erase(found-1, query.length()+1);
	}
	if(uri == "/EBDR")
		ffunc_write_out(session, me.getEBDRpage().c_str());
	else
		ffunc_write_out(session, "%s\n", "Error in URL");

	ffunc_str_t body;
	ffunc_read_body(session, &body); //ready body from actual session
	string line;					
	string intermediate;
	/*admin variables*/
	string busID_str = "";
	string busStops_str = "";

	// body process
	getline((istringstream)body.data, line); //get one line from body
	stringstream check(line);
	
	/* process body with structure 'busId=XXX&stops=X+X+X+X+X' */
	while (getline(check, intermediate, '&'))	// Separate the lines by & or end of string
	{	
		int begin_info = 0;
		size_t IDPos = intermediate.find("busID"); // locate 'busId' in body
		if(IDPos != string::npos) // checks if 'busID' exists
			for(string::iterator it = intermediate.begin() + IDPos; it != intermediate.end(); it++)
			{
				if(*it == '=')
					begin_info = 1; // From this char it should record in the string
				else if(begin_info)
					busID_str.push_back(*it); // Append char in the string
			}
		
		size_t stopsPos = intermediate.find("stops"); // locate 'stops' in body
		if(stopsPos!= string::npos) // checks if 'stops' exists
			for(string::iterator it = intermediate.begin() + stopsPos; it != intermediate.end(); it++)
			{
				if(*it == '=')
					begin_info = 1;	// From this char it should record in the string
				else if(begin_info)
					busStops_str.push_back(*it); // Append char in the string
			}
	}
	// ffunc_write_out(session, "%s\n", busID_str.c_str());
	// ffunc_write_out(session, "%s\n", busStops_str.c_str());
	int busId = 0; 
	vector <int> busStops;
	if(busID_str != "")
		busId = stoi(busID_str);
	
	if(busStops_str != "")
	{
		string tmp;
		for(string::iterator it = busStops_str.begin(); it != busStops_str.end(); it++)
		{
			if(*it != '+')
			{
				tmp.push_back(*it);
			}
			else
			{
				busStops.push_back(stoi(tmp));
				tmp = "";
			}
		}
		busStops.push_back(stoi(tmp));
	}
	
	ffunc_write_out(session, "Bus ID: %d\n", busId);
	if(!busStops.empty())
	{
		int i = 0;
		int aux = 0;
		for(vector<int>::iterator it = busStops.begin(); it != busStops.end(); it++)
		{
			if(aux == 0)
			{
				ffunc_write_out(session, "Bus Stop %d: (%d, ", ++i, *it);
				aux = 1;
			}
			else if(aux == 1)
			{
				ffunc_write_out(session, "%d) ", *it);
				aux = 0;
			}
		}
	}

	if (method == "POST" && uri == "/EBDR")
	{
		if(busId == 1)
			ffunc_write_out(session, me.getEBDRwrongID().c_str());
		else if(busStops.size() > 20)
			ffunc_write_out(session, me.getEBDRwrongBusStops().c_str());
		else if(busStops.size()%2 != 0)
		{
			ffunc_write_out(session, me.getEBDRinvalidBusStops().c_str());
		}
		else if(busId == 0 || busStops.size() == 0)
			ffunc_write_out(session, me.getEBDRinvalidNumber().c_str());
	}
}

//-----------------------------------------------------

FFUNC EBRMReqCallback(ffunc_session_t * session) {
	CServer me;
	char *pmet = ffunc_get_fcgi_param(session, "REQUEST_METHOD");
	string method(pmet);

	char *puri = ffunc_get_fcgi_param(session, "REQUEST_URI");
	string uri(puri);
	
	string query = "";
	if(session->query_str)
	{
		query = string(session->query_str);

		size_t found = uri.find(query);
		uri.erase(found-1, query.length()+1);
	}
	if(uri == "/EBRM")
		ffunc_write_out(session, me.getEBRMpage().c_str());
	else
		ffunc_write_out(session, "%s\n", "Error in URL");

	ffunc_str_t body;
	ffunc_read_body(session, &body); //ready body from actual session
	string line;					
	string intermediate;
	/*admin variables*/
	string busID_str = "";

	// body process
	getline((istringstream)body.data, line); //get one line from body
	stringstream check(line);
	
	/* process body with structure 'busID=XXX&newBusID=X+X+X+X+X' */
	while (getline(check, intermediate, '&'))	// Separate the lines by & or end of string
	{	
		int begin_info = 0;
		size_t IDPos = intermediate.find("busID"); // locate 'busID' in body
		if(IDPos != string::npos) // checks if 'busID' exists
			for(string::iterator it = intermediate.begin() + IDPos; it != intermediate.end(); it++)
			{
				if(*it == '=')
					begin_info = 1; // From this char it should record in the string
				else if(begin_info)
					busID_str.push_back(*it); // Append char in the string
			}
	}
	// ffunc_write_out(session, "%s\n", busID_str.c_str());
	// ffunc_write_out(session, "%s\n", busStops_str.c_str());
	int busId 		= 0; 
	if(busID_str != "")
		busId = stoi(busID_str);
	
	ffunc_write_out(session, "ID: %d\n", busId);
	

	if (method == "POST" && uri == "/EBRM")
	{
		if(busId == 1)
			ffunc_write_out(session, me.getEBRMwrongID().c_str());
		else if(busId == 0)
			ffunc_write_out(session, me.getEBRMinvalidNumber().c_str());		
	}
}

//-----------------------------------------------------

FFUNC ESIDReqCallback(ffunc_session_t * session) {
	CServer me;
	char *pmet = ffunc_get_fcgi_param(session, "REQUEST_METHOD");
	string method(pmet);

	char *puri = ffunc_get_fcgi_param(session, "REQUEST_URI");
	string uri(puri);
	
	string query = "";
	if(session->query_str)
	{
		query = string(session->query_str);

		size_t found = uri.find(query);
		uri.erase(found-1, query.length()+1);
	}
	if(uri == "/ESID")
		ffunc_write_out(session, me.getESIDpage().c_str());
	else
		ffunc_write_out(session, "%s\n", "Error in URL");

	ffunc_str_t body;
	ffunc_read_body(session, &body); //ready body from actual session
	string line;					
	string intermediate;
	/*admin variables*/
	string busID_str = "";
	string newBusID_str = "";

	// body process
	getline((istringstream)body.data, line); //get one line from body
	stringstream check(line);
	
	/* process body with structure 'busStopID=XXX&newBusStopID=XXXX' */
	while (getline(check, intermediate, '&'))	// Separate the lines by & or end of string
	{	
		int begin_info = 0;
		size_t IDPos = intermediate.find("busStopID"); // locate 'busID' in body
		if(IDPos != string::npos) // checks if 'busID' exists
			for(string::iterator it = intermediate.begin() + IDPos; it != intermediate.end(); it++)
			{
				if(*it == '=')
					begin_info = 1; // From this char it should record in the string
				else if(begin_info)
					busID_str.push_back(*it); // Append char in the string
			}
		
		size_t newIdPos = intermediate.find("newBusStopID"); // locate 'newBusID' in body
		if(newIdPos!= string::npos) // checks if 'newBusID' exists
			for(string::iterator it = intermediate.begin() + newIdPos; it != intermediate.end(); it++)
			{
				if(*it == '=')
					begin_info = 1;	// From this char it should record in the string
				else if(begin_info)
					newBusID_str.push_back(*it); // Append char in the string
			}
	}
	// ffunc_write_out(session, "%s\n", busID_str.c_str());
	// ffunc_write_out(session, "%s\n", busStops_str.c_str());
	int busId 		= 0; 
	int newBusId 	= 0;
	if(busID_str != "")
		busId = stoi(busID_str);

	if(newBusID_str != "")
		newBusId = stoi(newBusID_str);
	
	ffunc_write_out(session, "Current ID: %d\n New ID: %d\n", busId, newBusId);
	

	if (method == "POST" && uri == "/ESID")
	{
		if(busId == 1) // verify the existing bus stops
			ffunc_write_out(session, me.getESIDwrongCurID().c_str());
		else if(busId == 0 || newBusId == 0)
			ffunc_write_out(session, me.getESIDinvalidNumber().c_str());
		else if(newBusId == 2 || newBusId == busId)
			ffunc_write_out(session, me.getESIDwrongNewID().c_str());
		
	}
}

//-----------------------------------------------------

FFUNC ESRMReqCallback(ffunc_session_t * session) {
	CServer me;
	char *pmet = ffunc_get_fcgi_param(session, "REQUEST_METHOD");
	string method(pmet);

	char *puri = ffunc_get_fcgi_param(session, "REQUEST_URI");
	string uri(puri);
	
	string query = "";
	if(session->query_str)
	{
		query = string(session->query_str);

		size_t found = uri.find(query);
		uri.erase(found-1, query.length()+1);
	}
	if(uri == "/ESRM")
		ffunc_write_out(session, me.getESRMpage().c_str());
	else
		ffunc_write_out(session, "%s\n", "Error in URL");

	ffunc_str_t body;
	ffunc_read_body(session, &body); //ready body from actual session
	string line;					
	string intermediate;
	/*admin variables*/
	string busStopID_str = "";

	// body process
	getline((istringstream)body.data, line); //get one line from body
	stringstream check(line);
	
	/* process body with structure 'busStopID=XXX&newBusID=X+X+X+X+X' */
	while (getline(check, intermediate, '&'))	// Separate the lines by & or end of string
	{	
		int begin_info = 0;
		size_t IDPos = intermediate.find("busStopID"); // locate 'busID' in body
		if(IDPos != string::npos) // checks if 'busID' exists
			for(string::iterator it = intermediate.begin() + IDPos; it != intermediate.end(); it++)
			{
				if(*it == '=')
					begin_info = 1; // From this char it should record in the string
				else if(begin_info)
					busStopID_str.push_back(*it); // Append char in the string
			}
	}
	// ffunc_write_out(session, "%s\n", busID_str.c_str());
	// ffunc_write_out(session, "%s\n", busStops_str.c_str());
	int busStopId 		= 0; 
	if(busStopID_str != "")
		busStopId = stoi(busStopID_str);
	
	ffunc_write_out(session, "ID: %d\n", busStopId);
	

	if (method == "POST" && uri == "/ESRM")
	{
		if(busStopId == 1)
			ffunc_write_out(session, me.getESRMwrongID().c_str());
		else if(busStopId == 0)
			ffunc_write_out(session, me.getESRMinvalidNumber().c_str());		
	}
}

// ***********End of FastCGI Functions: **************
//====================================================
//====================================================
// ********************* Main: ***********************
int ffunc_main(int argc, char *argv[], ffunc_config_t *ffunc_conf) 
{
	try
	{
		CDaemons d;
		signal(SIGHUP,CDaemons::signalHandler);  /* catch hangup signal */
		signal(SIGTERM,CDaemons::signalHandler); /* catch kill signal   */
		signal(SIGUSR1,CDaemons::signalHandler); /* catch user signal   */	
		ffunc_conf->sock_port 		= 8000;
		ffunc_conf->backlog 		= 160;
		ffunc_conf->max_thread 		= 64;
		ffunc_conf->max_read_buffer = 131072;
		ffunc_parse_function(ffunc_conf, "userReqCallback", "busReqCallback", 
							"adminReqCallback", "ADBUReqCallback", "ADBSReqCallback", 
							"EBIDReqCallback", "EBDRReqCallback", "EBRMReqCallback", 
							"ESIDReqCallback", "ESRMReqCallback");
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
#ifdef __cplusplus
}
#endif

// *******************End of Main: *******************
//====================================================
//====================================================