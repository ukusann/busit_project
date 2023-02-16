#include <sys/syslog.h>
#include <sys/types.h> 
#include "CServer.h"
#include "ffunc.h"

#define ADMIN_NAME "matheus"
#define ADMIN_PASS "1234"

class CDaemons
{
private:
    pid_t pid;
    pid_t sid;
    void setInfo(); 
public:
    static void signalHandler(int sig);
    CDaemons();
    ~CDaemons();
    pid_t getPid();
};