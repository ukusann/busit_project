#ifndef __CServer__
#define __CServer__
#include <string>
#include "ffunc.h"


class CServer
{
private:
//====================================================
//**************** /bus html *************************
    std::string admin_form = 
    "Content-Type: text/html\r\n\r\n"
     "<!DOCTYPE html>\n"
    "<html>\n"
    "<body style=\"background-color:rgba(54, 160, 94, 0.692);\">\n"
        "<div style=\"border: 5px solid Black;background-color:rgba(0, 0, 0, 0.8);color:white;padding:20px;\">\n"
            "<h1><img src=\"../html_images/mini_busit.png\" alt=\"busit\" style=\"float:right;width:100px;height:100px;\">\n"
                "BUSIT - Administrator Page\n"
            "</h1>\n"
            "<p>Please login with the administrator credentials</p>\n"
            "<p>\n</p>\n"
        "</div>\n"     
        "<form action=\"/bus\" method=\"POST\">\n"
            "<fieldset style=\"background: #f6f8ff; border: 2px solid #4238ca;\">\n"
                "<legend>Admin Information</legend>\n"
                "<label for=\"username\">Username:</label><br>\n"
                "<input type=\"text\" id=\"username\" name=\"username\"><br>\n"
                "<label for=\"pwd\">Password:</label><br>\n"
                "<input type=\"password\" id=\"pwd\" name=\"pwd\">\n"
                "<button type=\"submit\">Submit</button>\n"
            "</fieldset>\n"
        "</form>\n"
    "</body>\n"
    "</html>\n";
                    
//-----------------------------------------------------
                        
    std::string bus_config = 
    "<!DOCTYPE html>\n"
    "<html>\n"
        "<body>\n"
            "<center>\n"
                "<h1>Welcome Administrator!</h1>\n"
                "<h2>\n"
                    "<a href=\"/admin\" method=\"POST\">\n"
                        "Continue\n"
                    "</a>\n" 
                "</h2>\n"
            "</center>\n"
        "</body>\n"
    "</html>\n";

//-----------------------------------------------------

    std::string answer_wrong_pass = 
    "<!DOCTYPE html>\n"
    "<html>\n"
        "<body>\n"
            "<center>\n"
                "<h1>Wrong Password, try again.</h1>\n"
                "<h2>\n"
                    "<a href=\"/bus\" method=\"POST\">\n"
                        "Try Again\n"
                    "</a>\n" 
                "</h2>\n"
            "</center>\n"
        "</body>\n"
    "</html>\n";

//-----------------------------------------------------
    
    std::string answer_wrong_name = 
    "<!DOCTYPE html>\n"
    "<html>\n"
        "<body>\n"
            "<center>\n"
                "<h1>User does not exist, try again.</h1>\n"
                "<h2>\n"
                    "<a href=\"/bus\" method=\"POST\">\n"
                        "Try Again\n"
                    "</a>\n" 
                "</h2>\n"
            "</center>\n"
        "</body>\n"
    "</html>\n";

//************End of /bus html ***********************
//====================================================
//====================================================
//**************** /admin html ***********************
    std::string admin_options =
    "Content-Type: text/html\r\n\r\n"
    "<!DOCTYPE html>\n"
    "<html>\n"
    "<body style=\"background-color:rgba(54, 160, 94, 0.692);\">\n"
        "<div style=\"border: 5px solid Black;background-color:rgba(0, 0, 0, 0.8);color:white;padding:20px;\">\n"
            "<h1><img src=\"../html_images/mini_busit.png\" alt=\"busit\" style=\"float:right;width:100px;height:100px;\">\n"
                "BUSIT - Administrator Page\n"
            "</h1>\n"
            "<p>Welcome Administrator!</p>\n"
            "<p>Please choose the configuration you want to make:</p>\n"
        "</div>\n" 
        "<h1>\n"
            "Bus Configurations:\n"
        "</h1>\n"

         "<h2>\n"
            "<a href=\"/ADBU\" method=\"POST\">\n"
                "Add Bus\n"
            "</a>\n" 
        "</h2>\n"

        "<h2>\n"
            "<a href=\"/EBID\" method=\"POST\">\n"
                "Edit Bus Id\n"
            "</a>\n" 
        "</h2>\n"

        "<h2>\n"
            "<a href=\"/EBDR\" method=\"POST\">\n"
                "Edit Bus Default Route\n"
            "</a>\n" 
        "</h2>\n"

        "<h2>\n"
            "<a href=\"/EBRM\" method=\"POST\">\n"
                "Remove Bus\n"
            "</a>\n" 
        "</h2>\n"

        "<h1>\n"
            "Bus Stop Configurations:\n"
        "</h1>\n"

         "<h2>\n"
            "<a href=\"/ADBS\" method=\"POST\">\n"
                "Add Bus Stop\n"
            "</a>\n" 
        "</h2>\n"

         "<h2>\n"
            "<a href=\"/ESID\" method=\"POST\">\n"
                "Edit Bus Stop ID\n"
            "</a>\n" 
        "</h2>\n"

        "<h2>\n"
            "<a href=\"/ESRM\" method=\"POST\">\n"
                "Remove Bus Stop\n"
            "</a>\n" 
        "</h2>\n"
   
    "</body>\n"
    "</html>\n";
//************End of /admin html ***********************
//======================================================
//======================================================
//**************** /user html **************************

    std::string user_options = 
    "Content-Type: text/html\r\n\r\n"
    "<!DOCTYPE html>\n"
    "<html>\n"
    "<body style=\"background-color:rgba(54, 160, 94, 0.692);\">\n"
        "<div style=\"border: 5px solid Black;background-color:rgba(0, 0, 0, 0.8);color:white;padding:20px;\">\n"
            "<h1><img src=\"../html_images/mini_busit.png\" alt=\"busit\" style=\"float:right;width:100px;height:100px;\">\n"
                "BUSIT - User Page\n"
            "</h1>\n"
            "<p>Welcome User!</p>\n"
            "<p>Please choose the action you want to make:</p>\n"
        "</div>\n" 
        "<h1>\n"
            "Options:\n"
        "</h1>\n"

         "<h2>\n"
            "<a href=\"/URBS\" method=\"POST\">\n"
                "Request Bus Stop\n"
            "</a>\n" 
        "</h2>\n"

        "<h2>\n"
            "<a href=\"/UCSR\" method=\"POST\">\n"
                "Get Bus Schedule\n"
            "</a>\n" 
        "</h2>\n"

        "<h2>\n"
            "<a href=\"/UCAT\" method=\"POST\">\n"
                "Check Bus Arrival Time\n"
            "</a>\n" 
        "</h2>\n"
   
    "</body>\n"
    "</html>\n";
//************End of /user html ************************
//======================================================
//======================================================
//**************** /ADBU html **************************

    std::string ADBU_form = 
    "Content-Type: text/html\r\n\r\n"
     "<!DOCTYPE html>\n"
    "<html>\n"
    "<body style=\"background-color:rgba(54, 160, 94, 0.692);\">\n"
        "<div style=\"border: 5px solid Black;background-color:rgba(0, 0, 0, 0.8);color:white;padding:20px;\">\n"
            "<h1><img src=\"../html_images/mini_busit.png\" alt=\"busit\" style=\"float:right;width:100px;height:100px;\">\n"
                "BUSIT - Bus Configuration\n"
            "</h1>\n"
            "<h2>Add Bus</h2>\n"
            "<p>\n</p>\n"
        "</div>\n"     
        "<form action=\"/ADBU\" method=\"POST\">\n"
            "<fieldset style=\"background: #f6f8ff; border: 2px solid #4238ca;\">\n"
                "<legend>Enter Bus information:</legend>\n"
                "<label for=\"busID\">Set bus id:</label><br>\n"
                "<input type=\"number\" id=\"busID\" name=\"busID\" min=\"1\"><br>\n"
                "<label for=\"stops\">Insert stops sequentially as x1 y1 x2 y2...</label><br>\n"
                "<input type=\"text\" id=\"stops\" name=\"stops\" ><br>\n"
                "<button type=\"submit\">Submit</button>\n"
            "</fieldset>\n"
        "</form>\n"
    "</body>\n"
    "</html>\n";

    //-----------------------------------------------------

    std::string ADBU_answer_wrong_busID = 
    "<!DOCTYPE html>\n"
    "<html>\n"
        "<body>\n"
            "<center>\n"
                "<h1>Bus already exists!, try again.</h1>\n"
                "<h2>\n"
                    "<a href=\"/ADBU\" method=\"POST\">\n"
                        "Try Again\n"
                    "</a>\n" 
                "</h2>\n"
            "</center>\n"
        "</body>\n"
    "</html>\n";

    //-----------------------------------------------------

    std::string ADBU_answer_wrong_busStops = 
    "<!DOCTYPE html>\n"
    "<html>\n"
        "<body>\n"
            "<center>\n"
                "<h1>Bus Stop(s) out of range!, try again.</h1>\n"
                "<h2>\n"
                    "<a href=\"/ADBU\" method=\"POST\">\n"
                        "Try Again\n"
                    "</a>\n" 
                "</h2>\n"
            "</center>\n"
        "</body>\n"
    "</html>\n";

     //-----------------------------------------------------

    std::string ADBU_answer_invalid_busStops = 
    "<!DOCTYPE html>\n"
    "<html>\n"
        "<body>\n"
            "<center>\n"
                "<h1>Error selecting bus stop(s)!, try again.</h1>\n"
                "<h2>\n"
                    "<a href=\"/ADBU\" method=\"POST\">\n"
                        "Try Again\n"
                    "</a>\n" 
                "</h2>\n"
            "</center>\n"
        "</body>\n"
    "</html>\n";

    //-----------------------------------------------------

    std::string ADBU_answer_invalid_number = 
    "<!DOCTYPE html>\n"
    "<html>\n"
        "<body>\n"
            "<center>\n"
                "<h1>Invalid Number!, try again.</h1>\n"
                "<h2>\n"
                    "<a href=\"/ADBU\" method=\"POST\">\n"
                        "Try Again\n"
                    "</a>\n" 
                "</h2>\n"
            "</center>\n"
        "</body>\n"
    "</html>\n";

//************End of /ADBU html ************************
//======================================================
//======================================================
//**************** /ADBS html **************************

    std::string ADBS_form = 
    "Content-Type: text/html\r\n\r\n"
     "<!DOCTYPE html>\n"
    "<html>\n"
    "<body style=\"background-color:rgba(54, 160, 94, 0.692);\">\n"
        "<div style=\"border: 5px solid Black;background-color:rgba(0, 0, 0, 0.8);color:white;padding:20px;\">\n"
            "<h1><img src=\"../html_images/mini_busit.png\" alt=\"busit\" style=\"float:right;width:100px;height:100px;\">\n"
                "BUSIT - Bus Stop Configuration\n"
            "</h1>\n"
            "<h2>Add Bus Stop</h2>\n"
            "<p>\n</p>\n"
        "</div>\n"     
        "<form action=\"/ADBS\" method=\"POST\">\n"
            "<fieldset style=\"background: #f6f8ff; border: 2px solid #4238ca;\">\n"
                "<legend>Enter Bus Stop information:</legend>\n"
                "<label for=\"busStopID\">Set bus stop id:</label><br>\n"
                "<input type=\"number\" id=\"busStopID\" name=\"busStopID\" min=\"1\"><br>\n"
                "<label for=\"coord\">Insert bus stop coord as x y:</label><br>\n"
                "<input type=\"text\" id=\"coord\" name=\"coord\" ><br>\n"
                "<button type=\"submit\">Submit</button>\n"
            "</fieldset>\n"
        "</form>\n"
    "</body>\n"
    "</html>\n";

    //-----------------------------------------------------

    std::string ADBS_answer_wrong_busStopID = 
    "<!DOCTYPE html>\n"
    "<html>\n"
        "<body>\n"
            "<center>\n"
                "<h1>Bus Stop already exists!, try again.</h1>\n"
                "<h2>\n"
                    "<a href=\"/ADBS\" method=\"POST\">\n"
                        "Try Again\n"
                    "</a>\n" 
                "</h2>\n"
            "</center>\n"
        "</body>\n"
    "</html>\n";

    //-----------------------------------------------------

    std::string ADBS_answer_wrong_busStops = 
    "<!DOCTYPE html>\n"
    "<html>\n"
        "<body>\n"
            "<center>\n"
                "<h1>Bus Stop out of range!, try again.</h1>\n"
                "<h2>\n"
                    "<a href=\"/ADBS\" method=\"POST\">\n"
                        "Try Again\n"
                    "</a>\n" 
                "</h2>\n"
            "</center>\n"
        "</body>\n"
    "</html>\n";

    //-----------------------------------------------------

    std::string ADBS_answer_invalid_number = 
    "<!DOCTYPE html>\n"
    "<html>\n"
        "<body>\n"
            "<center>\n"
                "<h1>Invalid Number!, try again.</h1>\n"
                "<h2>\n"
                    "<a href=\"/ADBS\" method=\"POST\">\n"
                        "Try Again\n"
                    "</a>\n" 
                "</h2>\n"
            "</center>\n"
        "</body>\n"
    "</html>\n";

//************End of /ADBS html ************************
//======================================================
//======================================================
//**************** /EBID html **************************

    std::string EBID_form = 
    "Content-Type: text/html\r\n\r\n"
     "<!DOCTYPE html>\n"
    "<html>\n"
    "<body style=\"background-color:rgba(54, 160, 94, 0.692);\">\n"
        "<div style=\"border: 5px solid Black;background-color:rgba(0, 0, 0, 0.8);color:white;padding:20px;\">\n"
            "<h1><img src=\"../html_images/mini_busit.png\" alt=\"busit\" style=\"float:right;width:100px;height:100px;\">\n"
                "BUSIT - Bus Configuration\n"
            "</h1>\n"
            "<h2>Edit Bus ID</h2>\n"
            "<p>\n</p>\n"
        "</div>\n"     
        "<form action=\"/EBID\" method=\"POST\">\n"
            "<fieldset style=\"background: #f6f8ff; border: 2px solid #4238ca;\">\n"
                "<legend>Enter Bus ID informations:</legend>\n"
                "<label for=\"busID\">Enter current Bus ID:</label><br>\n"
                "<input type=\"number\" id=\"busID\" name=\"busID\" min=\"1\"><br>\n"
                "<label for=\"newBusID\">Enter new Bus ID:</label><br>\n"
                "<input type=\"number\" id=\"newBusID\" name=\"newBusID\" min=\"1\"><br>\n"
                "<button type=\"submit\">Submit</button>\n"
            "</fieldset>\n"
        "</form>\n"
    "</body>\n"
    "</html>\n";

    //-----------------------------------------------------

    std::string EBID_answer_wrong_current_busID = 
    "<!DOCTYPE html>\n"
    "<html>\n"
        "<body>\n"
            "<center>\n"
                "<h1>Current Bus ID does not exist!, try again.</h1>\n"
                "<h2>\n"
                    "<a href=\"/EBID\" method=\"POST\">\n"
                        "Try Again\n"
                    "</a>\n" 
                "</h2>\n"
            "</center>\n"
        "</body>\n"
    "</html>\n";


    //-----------------------------------------------------

    std::string EBID_answer_wrong_new_busID = 
    "<!DOCTYPE html>\n"
    "<html>\n"
        "<body>\n"
            "<center>\n"
                "<h1>Invalid new Bus ID! ID already exists!, try again.</h1>\n"
                "<h2>\n"
                    "<a href=\"/EBID\" method=\"POST\">\n"
                        "Try Again\n"
                    "</a>\n" 
                "</h2>\n"
            "</center>\n"
        "</body>\n"
    "</html>\n";

    //-----------------------------------------------------

    std::string EBID_answer_invalid_number = 
    "<!DOCTYPE html>\n"
    "<html>\n"
        "<body>\n"
            "<center>\n"
                "<h1>Invalid Number!, try again.</h1>\n"
                "<h2>\n"
                    "<a href=\"/EBID\" method=\"POST\">\n"
                        "Try Again\n"
                    "</a>\n" 
                "</h2>\n"
            "</center>\n"
        "</body>\n"
    "</html>\n";

//************End of /EBID html ************************
//======================================================
//======================================================
//**************** /EBDR html **************************


    std::string EBDR_form = 
    "Content-Type: text/html\r\n\r\n"
     "<!DOCTYPE html>\n"
    "<html>\n"
    "<body style=\"background-color:rgba(54, 160, 94, 0.692);\">\n"
        "<div style=\"border: 5px solid Black;background-color:rgba(0, 0, 0, 0.8);color:white;padding:20px;\">\n"
            "<h1><img src=\"../html_images/mini_busit.png\" alt=\"busit\" style=\"float:right;width:100px;height:100px;\">\n"
                "BUSIT - Bus Configuration\n"
            "</h1>\n"
            "<h2>Edit Bus Default Route</h2>\n"
            "<p>\n</p>\n"
        "</div>\n"     
        "<form action=\"/EBDR\" method=\"POST\">\n"
            "<fieldset style=\"background: #f6f8ff; border: 2px solid #4238ca;\">\n"
                "<legend>Enter Bus information:</legend>\n"
                "<label for=\"busID\">Bus id:</label><br>\n"
                "<input type=\"number\" id=\"busID\" name=\"busID\" min=\"1\"><br>\n"
                "<label for=\"stops\">Insert new stops sequentially as x1 y1 x2 y2...</label><br>\n"
                "<input type=\"text\" id=\"stops\" name=\"stops\" ><br>\n"
                "<button type=\"submit\">Submit</button>\n"
            "</fieldset>\n"
        "</form>\n"
    "</body>\n"
    "</html>\n";


    //-----------------------------------------------------

    std::string EBDR_answer_wrong_busID = 
    "<!DOCTYPE html>\n"
    "<html>\n"
        "<body>\n"
            "<center>\n"
                "<h1>Bus does not exist!, try again.</h1>\n"
                "<h2>\n"
                    "<a href=\"/EBDR\" method=\"POST\">\n"
                        "Try Again\n"
                    "</a>\n" 
                "</h2>\n"
            "</center>\n"
        "</body>\n"
    "</html>\n";

    //-----------------------------------------------------

    std::string EBDR_answer_wrong_busStops = 
    "<!DOCTYPE html>\n"
    "<html>\n"
        "<body>\n"
            "<center>\n"
                "<h1>Bus Stop(s) out of range!, try again.</h1>\n"
                "<h2>\n"
                    "<a href=\"/EBDR\" method=\"POST\">\n"
                        "Try Again\n"
                    "</a>\n" 
                "</h2>\n"
            "</center>\n"
        "</body>\n"
    "</html>\n";

     //-----------------------------------------------------

    std::string EBDR_answer_invalid_busStops = 
    "<!DOCTYPE html>\n"
    "<html>\n"
        "<body>\n"
            "<center>\n"
                "<h1>Error selecting bus stop(s)!, try again.</h1>\n"
                "<h2>\n"
                    "<a href=\"/EBDR\" method=\"POST\">\n"
                        "Try Again\n"
                    "</a>\n" 
                "</h2>\n"
            "</center>\n"
        "</body>\n"
    "</html>\n";

    //-----------------------------------------------------

    std::string EBDR_answer_invalid_number = 
    "<!DOCTYPE html>\n"
    "<html>\n"
        "<body>\n"
            "<center>\n"
                "<h1>Invalid Number!, try again.</h1>\n"
                "<h2>\n"
                    "<a href=\"/EBDR\" method=\"POST\">\n"
                        "Try Again\n"
                    "</a>\n" 
                "</h2>\n"
            "</center>\n"
        "</body>\n"
    "</html>\n";

//************End of /EBDR html ************************
//======================================================
//======================================================
//**************** /EBRM html **************************

    std::string EBRM_form = 
    "Content-Type: text/html\r\n\r\n"
     "<!DOCTYPE html>\n"
    "<html>\n"
    "<body style=\"background-color:rgba(54, 160, 94, 0.692);\">\n"
        "<div style=\"border: 5px solid Black;background-color:rgba(0, 0, 0, 0.8);color:white;padding:20px;\">\n"
            "<h1><img src=\"../html_images/mini_busit.png\" alt=\"busit\" style=\"float:right;width:100px;height:100px;\">\n"
                "BUSIT - Bus Configuration\n"
            "</h1>\n"
            "<h2>Remove Bus</h2>\n"
            "<p>\n</p>\n"
        "</div>\n"     
        "<form action=\"/EBRM\" method=\"POST\">\n"
            "<fieldset style=\"background: #f6f8ff; border: 2px solid #4238ca;\">\n"
                "<legend>Enter Bus information:</legend>\n"
                "<label for=\"busID\">Bus id:</label><br>\n"
                "<input type=\"number\" id=\"busID\" name=\"busID\" min=\"1\"><br>\n"
                "<button type=\"submit\">Submit</button>\n"
            "</fieldset>\n"
        "</form>\n"
    "</body>\n"
    "</html>\n";


    //-----------------------------------------------------

    std::string EBRM_answer_wrong_busID = 
    "<!DOCTYPE html>\n"
    "<html>\n"
        "<body>\n"
            "<center>\n"
                "<h1>Bus does not exist!, try again.</h1>\n"
                "<h2>\n"
                    "<a href=\"/EBRM\" method=\"POST\">\n"
                        "Try Again\n"
                    "</a>\n" 
                "</h2>\n"
            "</center>\n"
        "</body>\n"
    "</html>\n";

    //-----------------------------------------------------

    std::string EBRM_answer_invalid_number = 
    "<!DOCTYPE html>\n"
    "<html>\n"
        "<body>\n"
            "<center>\n"
                "<h1>Invalid Number!, try again.</h1>\n"
                "<h2>\n"
                    "<a href=\"/EBRM\" method=\"POST\">\n"
                        "Try Again\n"
                    "</a>\n" 
                "</h2>\n"
            "</center>\n"
        "</body>\n"
    "</html>\n";   

//************End of /EBRM html ************************
//======================================================
//======================================================
//**************** /ESID html **************************

    std::string ESID_form = 
    "Content-Type: text/html\r\n\r\n"
     "<!DOCTYPE html>\n"
    "<html>\n"
    "<body style=\"background-color:rgba(54, 160, 94, 0.692);\">\n"
        "<div style=\"border: 5px solid Black;background-color:rgba(0, 0, 0, 0.8);color:white;padding:20px;\">\n"
            "<h1><img src=\"../html_images/mini_busit.png\" alt=\"busit\" style=\"float:right;width:100px;height:100px;\">\n"
                "BUSIT - Bus Stop Configuration\n"
            "</h1>\n"
            "<h2>Edit Bus Stop ID</h2>\n"
            "<p>\n</p>\n"
        "</div>\n"     
        "<form action=\"/ESID\" method=\"POST\">\n"
            "<fieldset style=\"background: #f6f8ff; border: 2px solid #4238ca;\">\n"
                "<legend>Enter Bus Stop ID informations:</legend>\n"
                "<label for=\"busStopID\">Enter current Bus ID:</label><br>\n"
                "<input type=\"number\" id=\"busStopID\" name=\"busStopID\" min=\"1\"><br>\n"
                "<label for=\"newBusStopID\">Enter new Bus Stop ID:</label><br>\n"
                "<input type=\"number\" id=\"newBusStopID\" name=\"newBusStopID\" min=\"1\"><br>\n"
                "<button type=\"submit\">Submit</button>\n"
            "</fieldset>\n"
        "</form>\n"
    "</body>\n"
    "</html>\n";

    //-----------------------------------------------------

    std::string ESID_answer_wrong_current_busID = 
    "<!DOCTYPE html>\n"
    "<html>\n"
        "<body>\n"
            "<center>\n"
                "<h1>Current Bus Stop ID does not exist!, try again.</h1>\n"
                "<h2>\n"
                    "<a href=\"/ESID\" method=\"POST\">\n"
                        "Try Again\n"
                    "</a>\n" 
                "</h2>\n"
            "</center>\n"
        "</body>\n"
    "</html>\n";


    //-----------------------------------------------------

    std::string ESID_answer_wrong_new_busID = 
    "<!DOCTYPE html>\n"
    "<html>\n"
        "<body>\n"
            "<center>\n"
                "<h1>Invalid new Bus Stop ID! ID already exists!, try again.</h1>\n"
                "<h2>\n"
                    "<a href=\"/ESID\" method=\"POST\">\n"
                        "Try Again\n"
                    "</a>\n" 
                "</h2>\n"
            "</center>\n"
        "</body>\n"
    "</html>\n";

    //-----------------------------------------------------

    std::string ESID_answer_invalid_number = 
    "<!DOCTYPE html>\n"
    "<html>\n"
        "<body>\n"
            "<center>\n"
                "<h1>Invalid Number!, try again.</h1>\n"
                "<h2>\n"
                    "<a href=\"/ESID\" method=\"POST\">\n"
                        "Try Again\n"
                    "</a>\n" 
                "</h2>\n"
            "</center>\n"
        "</body>\n"
    "</html>\n";

//************End of /ESID html ************************
//======================================================
//======================================================
//**************** /ESRM html **************************

    std::string ESRM_form = 
    "Content-Type: text/html\r\n\r\n"
     "<!DOCTYPE html>\n"
    "<html>\n"
    "<body style=\"background-color:rgba(54, 160, 94, 0.692);\">\n"
        "<div style=\"border: 5px solid Black;background-color:rgba(0, 0, 0, 0.8);color:white;padding:20px;\">\n"
            "<h1><img src=\"../html_images/mini_busit.png\" alt=\"busit\" style=\"float:right;width:100px;height:100px;\">\n"
                "BUSIT - Bus Stop Configuration\n"
            "</h1>\n"
            "<h2>Remove Bus Stop</h2>\n"
            "<p>\n</p>\n"
        "</div>\n"     
        "<form action=\"/ESRM\" method=\"POST\">\n"
            "<fieldset style=\"background: #f6f8ff; border: 2px solid #4238ca;\">\n"
                "<legend>Enter Bus Stop information:</legend>\n"
                "<label for=\"busStopID\">Bus id:</label><br>\n"
                "<input type=\"number\" id=\"busStopID\" name=\"busStopID\" min=\"1\"><br>\n"
                "<button type=\"submit\">Submit</button>\n"
            "</fieldset>\n"
        "</form>\n"
    "</body>\n"
    "</html>\n";


    //-----------------------------------------------------

    std::string ESRM_answer_wrong_busID = 
    "<!DOCTYPE html>\n"
    "<html>\n"
        "<body>\n"
            "<center>\n"
                "<h1>Bus Stop does not exist!, try again.</h1>\n"
                "<h2>\n"
                    "<a href=\"/ESRM\" method=\"POST\">\n"
                        "Try Again\n"
                    "</a>\n" 
                "</h2>\n"
            "</center>\n"
        "</body>\n"
    "</html>\n";

    //-----------------------------------------------------

    std::string ESRM_answer_invalid_number = 
    "<!DOCTYPE html>\n"
    "<html>\n"
        "<body>\n"
            "<center>\n"
                "<h1>Invalid Number!, try again.</h1>\n"
                "<h2>\n"
                    "<a href=\"/ESRM\" method=\"POST\">\n"
                        "Try Again\n"
                    "</a>\n" 
                "</h2>\n"
            "</center>\n"
        "</body>\n"
    "</html>\n";  
public:
    CServer();
    ~CServer();
    //=================================
    //**************bus****************
    std::string getAdminForm();
    std::string getBusConfigPage();
    std::string getAnswerWrongPass();
    std::string getAnswerWrongName();

    //===================================
    //**************admin****************
    std::string getAdminPage();
    
    //==================================
    //**************user****************
    std::string getUserPage();

    //==================================
    //**************ADBU****************
    std::string getADBUpage();
    std::string getADBUwrongID();
    std::string getADBUwrongBusStops();
    std::string getADBUinvalidBusStops();
    std::string getADBUinvalidNumber();

    //==================================
    //**************ADBS****************
    std::string getADBSpage();
    std::string getADBSwrongID();
    std::string getADBSinvalidBusStop();
    std::string getADBSinvalidNumber();

    //==================================
    //**************EBID****************
    std::string getEBIDpage();
    std::string getEBIDwrongCurID();
    std::string getEBIDwrongNewID();
    std::string getEBIDinvalidNumber();

    //==================================
    //**************EBDR****************
    std::string getEBDRpage();
    std::string getEBDRwrongID();
    std::string getEBDRwrongBusStops();
    std::string getEBDRinvalidBusStops();
    std::string getEBDRinvalidNumber();

    //==================================
    //**************EBRM****************
    std::string getEBRMpage();
    std::string getEBRMwrongID();
    std::string getEBRMinvalidNumber();

    //==================================
    //**************ESID****************
    std::string getESIDpage();
    std::string getESIDwrongCurID();
    std::string getESIDwrongNewID();
    std::string getESIDinvalidNumber();

    //==================================
    //**************ESRM****************
    std::string getESRMpage();
    std::string getESRMwrongID();
    std::string getESRMinvalidNumber();
};
#endif  /*__CServer__*/