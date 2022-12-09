#include <sys/syslog.h>
#include <sys/types.h> 

class CDaemons
{
private:
    pid_t pid;
    pid_t sid;
    int len;
    int fd;
    bool exit_flag;
    time_t timebuf;
    void setInfo(); 
    static void exitCall();
    static void signalHandler(int sig);
public:
    CDaemons();
    ~CDaemons();
    void idle();
};