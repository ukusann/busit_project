#include <sys/syslog.h>
#include <sys/types.h> 

class CDaemons
{
private:
    pid_t pid;
    pid_t sid;
    int len;
    int fd;
    time_t timebuf;
    void setInfo(); 
public:
    static void signalHandler(int sig);
    CDaemons();
    ~CDaemons();
    void idle();
    pid_t getPid();
};