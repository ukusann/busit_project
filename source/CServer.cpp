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
	bool login_check = 0;

	// body process
	getline((istringstream)body.data, line);
	stringstream check(line);
	
	while (getline(check, intermediate, '&'))
	{	
		int begin_info = 0;
		size_t namePos = intermediate.find("username");
		if(namePos != string::npos)
			for(string::iterator it = intermediate.begin() + namePos; it != intermediate.end(); it++)
			{
				if(*it == '=')
					begin_info = 1;
				else if(begin_info)
					admin_name.push_back(*it);
			}
		
		size_t passPos = intermediate.find("pwd");
		if(passPos!= string::npos)
			for(string::iterator it = intermediate.begin() + passPos; it != intermediate.end(); it++)
			{
				if(*it == '=')
					begin_info = 1;
				else if(begin_info)
					admin_pass.push_back(*it);
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
	ffunc_write_out(session, "Status: 200 OK\r\n");
	ffunc_write_out(session, "Content-Type: text/plain\r\n\r\n");/* \r\n\r\n  means go to response message*/
	ffunc_write_out(session, "%s\n", "User callback"); 

	CServer me;
	std::vector<int> a;
	a.push_back(1);

	if (session->query_str) {
		char *out = (char*) ffunc_get_query_param(session, "userId", sizeof("userId")- 1);
		if (out)
			ffunc_write_out(session, "output= %s\n", out); 
	}
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
		ffunc_write_out(session, me.getAdminForm().c_str());
	else
		ffunc_write_out(session, "%s\n", "Error in URL");
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
		ffunc_write_out(session, me.getAdminForm().c_str());
	else
		ffunc_write_out(session, "%s\n", "Error in URL");
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
		ffunc_write_out(session, me.getAdminForm().c_str());
	else
		ffunc_write_out(session, "%s\n", "Error in URL");
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
		ffunc_write_out(session, me.getAdminForm().c_str());
	else
		ffunc_write_out(session, "%s\n", "Error in URL");
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
		ffunc_write_out(session, me.getAdminForm().c_str());
	else
		ffunc_write_out(session, "%s\n", "Error in URL");
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
		ffunc_write_out(session, me.getAdminForm().c_str());
	else
		ffunc_write_out(session, "%s\n", "Error in URL");
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
		ffunc_write_out(session, me.getAdminForm().c_str());
	else
		ffunc_write_out(session, "%s\n", "Error in URL");
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
