#include "CServer.h"
#include <iostream>
#include <vector>
#include <string.h>


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

