#ifndef __CServer__
#define __CServer__
#include <string>
#include "ffunc.h"


class CServer
{
private:
//====================================================
//**************** /bus strings **********************
    std::string admin_form = 
    "Content-Type: text/html\r\n\r\n"
    "<form action=\"/bus\" method=\"POST\">\n"
        "<fieldset style=\"background: #f6f8ff; border: 2px solid #4238ca;\">\n"
            "<legend>Admin Information</legend>\n"
            "<label for=\"username\">Username:</label><br>\n"
            "<input type=\"text\" id=\"username\" name=\"username\"><br>\n"
            "<label for=\"pwd\">Password:</label><br>\n"
            "<input type=\"password\" id=\"pwd\" name=\"pwd\">\n"
            "<button type=\"submit\">Submit</button>\n"
        "</fieldset>\n"
    "</form>\n";
                        
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

// ***********End of /bus strings ********************
//====================================================
//====================================================
//**************** /admin Strings ********************
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
// ***********End of /admin strings ********************
//======================================================
//======================================================
//**************** /user Strings ***********************

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
// ***********End of /user strings ********************
//======================================================
public:
    CServer();
    ~CServer();
    //***********/bus
    std::string getAdminForm();
    std::string getBusConfigPage();
    std::string getAnswerWrongPass();
    std::string getAnswerWrongName();
    std::string getAdminPage();
    std::string getUserPage();

};
#endif  /*__CServer__*/