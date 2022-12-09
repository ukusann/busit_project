#include "CDaemons.h"
#include <stdexcept>
#include <unistd.h> 
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <cstring>
#include <iostream>
using namespace std;

//===========================================================
//===========================================================
// ***********Beginning of Static Variables: ****************

bool CDaemons::exit_flag = false;

// ***********End of Static Variables: **********************
//===========================================================
//===========================================================
// ***********Beginning of Constructor/Destructor: **********
CDaemons::CDaemons()
    : fd(0)
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

    this->len = strlen(ctime(&this->timebuf));
}

//-----------------------------------------------------------

void CDaemons::signalHandler(int sig)
{
    switch(sig) {
		case SIGHUP:
			syslog(LOG_INFO,"Hangup signal catched");
			break;

        case SIGUSR1:
			CDaemons::exit_flag = true;
            syslog(LOG_INFO,"User signal catched");
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

void CDaemons::idle()
{
    signal(SIGHUP,signalHandler); /* catch hangup signal */
	signal(SIGTERM,signalHandler); /* catch kill signal */
    signal(SIGUSR1,signalHandler); /* catch user signal */
    while (~this->exit_flag) 
	{
		char *buf = (char *)malloc(sizeof(char) + len + 1);
		if (buf == NULL) {
			perror("malloc");
			throw length_error("Buf creation incomplete!");
			exit(EXIT_FAILURE);
		}
		if ((fd = open("/var/log/daemons.log",	O_CREAT | O_WRONLY | O_APPEND, 0600)) < 0) {
			perror("open");
			throw runtime_error("Could not open log file!");
			exit(EXIT_FAILURE);
		}
		time((time_t*)&timebuf);
		strncpy(buf, ctime(&timebuf), len + 1);
		write(fd, buf, len + 1);
		close(fd);
		sleep(15);
	}
	syslog(LOG_INFO,"EXITING DAEMON LOOP!");
    exit(EXIT_SUCCESS);	
}

// ***********End of Public Functions: **********************
//===========================================================
//===========================================================
