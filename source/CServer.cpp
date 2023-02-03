#include "CServer.h"
#include <iostream>
#include <vector>
#include <string.h>
#include <sstream>

using namespace std;

#define ADMIN_NAME "matheus"
#define ADMIN_PASS "1234"
/***
g++ file.cpp -I../ ../ffunc.c -lfcgi -pthread -ldl -rdynamic
**/

//=====================================================
//=====================================================
// ***********Beginning of Constructor/Destructor: ****

CServer::CServer() 
{
	printf("%s\n", "Server request!");
}

//------------------------------------------------

CServer::~CServer() 
{
	printf("%s\n", "Request handled!");
}

// ***********End of Constructor/Destructor: *********
//====================================================
//====================================================
//**************** Public Funtions *******************

string CServer::getAdminForm()
{
	return this->admin_form;
}

//-----------------------------------------------------

string CServer::getBusConfigPage()
{
	return this->bus_config;
}

//-----------------------------------------------------

string CServer::getAnswerWrongPass()
{
	return this->answer_wrong_pass;
}

//-----------------------------------------------------

string CServer::getAnswerWrongName()
{
	return this->answer_wrong_name;
}

//-----------------------------------------------------

string CServer::getAdminPage()
{
	return this->admin_options;
}

//-----------------------------------------------------

string CServer::getUserPage()
{
	return this->user_options;
}

//-----------------------------------------------------

string CServer::getADBUpage()
{
	return this->ADBU_form;
}

//-----------------------------------------------------

string CServer::getADBUwrongID()
{
	return this->ADBU_answer_wrong_busID;
}

//-----------------------------------------------------

string CServer::getADBUwrongBusStops()
{
	return this->ADBU_answer_wrong_busStops;
}

//-----------------------------------------------------

string CServer::getADBUinvalidBusStops()
{
	return this->ADBU_answer_invalid_busStops;
}

//-----------------------------------------------------

string CServer::getADBUinvalidNumber()
{
	return this->ADBU_answer_invalid_number;
}

//-----------------------------------------------------

string CServer::getADBSpage()
{
	return this->ADBS_form;
}

//-----------------------------------------------------

string CServer::getADBSwrongID()
{
	return this->ADBS_answer_wrong_busStopID;
}

//-----------------------------------------------------

string CServer::getADBSinvalidBusStop()
{
	return this->ADBS_answer_wrong_busStops;
}

//-----------------------------------------------------

string CServer::getADBSinvalidNumber()
{
	return this->ADBS_answer_invalid_number;
}

//-----------------------------------------------------

string CServer::getEBIDpage()
{
	return this->EBID_form;
}

//-----------------------------------------------------

string CServer::getEBIDwrongCurID()
{
	return this->EBID_answer_wrong_current_busID;
}

//-----------------------------------------------------

string CServer::getEBIDwrongNewID()
{
	return this->EBID_answer_wrong_new_busID;
}

//-----------------------------------------------------

string CServer::getEBIDinvalidNumber()
{
	return this->EBID_answer_invalid_number;
}

//-----------------------------------------------------

string CServer::getEBDRpage()
{
	return this->EBDR_form;
}

//-----------------------------------------------------

string CServer::getEBDRwrongID()
{
	return this->EBDR_answer_wrong_busID;
}

//-----------------------------------------------------

string CServer::getEBDRwrongBusStops()
{
	return this->EBDR_answer_wrong_busStops;
}

//-----------------------------------------------------

string CServer::getEBDRinvalidBusStops()
{
	return this->EBDR_answer_invalid_busStops;
}

//-----------------------------------------------------

string CServer::getEBDRinvalidNumber()
{
	return this->EBDR_answer_invalid_number;
}

//-----------------------------------------------------

string CServer::getEBRMpage()
{
	return this->EBRM_form;
}

//-----------------------------------------------------

string CServer::getEBRMwrongID()
{
	return this->EBRM_answer_wrong_busID;
}

//-----------------------------------------------------

string CServer::getEBRMinvalidNumber()
{
	return this->EBRM_answer_invalid_number;
}

//-----------------------------------------------------

string CServer::getESIDpage()
{
	return this->ESID_form;
}

//-----------------------------------------------------

string CServer::getESIDwrongCurID()
{
	return this->ESID_answer_wrong_current_busID;
}

//-----------------------------------------------------

string CServer::getESIDwrongNewID()
{
	return this->ESID_answer_wrong_new_busID;
}

//-----------------------------------------------------

string CServer::getESIDinvalidNumber()
{
	return this->ESID_answer_invalid_number;
}

//-----------------------------------------------------

string CServer::getESRMpage()
{
	return this->ESRM_form;
}

//-----------------------------------------------------

string CServer::getESRMwrongID()
{
	return this->ESRM_answer_wrong_busID;
}

//-----------------------------------------------------

string CServer::getESRMinvalidNumber()
{
	return this->ESRM_answer_invalid_number;
}
// ***********End of Public Functions: ***************
//====================================================
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

FFUNC postError(ffunc_session_t * session) {
	ffunc_write_out(session, "Status: 500 Internal Server Error\r\n");
	ffunc_write_out(session, "Content-Type: text/plain\r\n\r\n");
	ffunc_write_out(session, "%s\n", "you hitting error");
}

//-----------------------------------------------------

FFUNC mainReqCallback(ffunc_session_t * session) {
	ffunc_write_out(session, "Status: 200 OK\r\n");
	ffunc_write_out(session, "Content-Type: text/plain\r\n\r\n");/* \r\n\r\n  means go to response message*/
	ffunc_write_out(session, "%s\n", "Main Callback");

	CServer me;
	std::vector<int> a;
	a.push_back(1);

	if (session->query_str) {
		char *out = (char*) ffunc_get_query_param(session, "userId", sizeof("userId")- 1);
		if (out)
			ffunc_write_out(session, "output= %s\n", out); //cjson undefined because only use it's own file
	}
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
	// ffunc_write_out(session, "%s\n", admin_name.c_str());
	// ffunc_write_out(session, "%s\n", admin_pass.c_str());
	

	if (method == "POST" && uri == "/bus")
	{
		if(admin_name.compare(ADMIN_NAME) == 0)
			if(admin_pass.compare(ADMIN_PASS) == 0)
				ffunc_write_out(session, me.getBusConfigPage().c_str());
			else
				ffunc_write_out(session, me.getAnswerWrongPass().c_str());
		else
			ffunc_write_out(session, me.getAnswerWrongName().c_str());

		//ffunc_write_out(session, "Query String %s\n", query.c_str());
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


int ffunc_main(int argc, char *argv[], ffunc_config_t *ffunc_conf) {
	ffunc_conf->sock_port 		= 8000;
	ffunc_conf->backlog 		= 160;
	ffunc_conf->max_thread 		= 64;
	//ffunc_conf->daemon 			= 1;
	ffunc_conf->max_read_buffer = 131072;
	ffunc_parse_function(ffunc_conf, "postError", "mainReqCallback", "userReqCallback", "busReqCallback", 
						"adminReqCallback", "ADBUReqCallback", "ADBSReqCallback", "EBIDReqCallback", "EBDRReqCallback",
						"EBRMReqCallback", "ESIDReqCallback", "ESRMReqCallback");
	return 0;
}

#ifdef __cplusplus
}
#endif
// *******************End of Main: *******************
//====================================================
//====================================================
