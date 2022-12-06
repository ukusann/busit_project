#include  <sys/syslog.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <unistd.h> 
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <stdio.h> 
#include <fcntl.h>
#include <time.h>
#include <signal.h>

using namespace std;

void signal_handler(int sig) {
	switch(sig) {
		case SIGHUP:
			syslog(LOG_INFO,"Hangup signal catched");
			break;

        case SIGUSR1:
            syslog(LOG_INFO,"User signal catched");
            break;

		case SIGTERM:
			syslog(LOG_INFO,"Terminate signal catched");
			exit(0);
			break;
	}
}



int main(int argc, char *argv[]){
	pid_t pid, sid;
	int len, fd;
	time_t timebuf;

	pid = fork(); // create a new process

	if (pid < 0) { // on error exit
		syslog(LOG_ERR, "%s\n", "fork");
		exit(EXIT_FAILURE);
	}

	if (pid > 0){  
		printf("Deamon PID: %d\n", pid);	
		exit(EXIT_SUCCESS); // parent process (exit)
	}
	sid = setsid(); // create a new session

	if (sid < 0) { // on error exit
		syslog(LOG_ERR, "%s\n", "setsid");
		exit(EXIT_FAILURE);
	}
	// make '/' the root directory
	if (chdir("/") < 0) { // on error exit
		syslog(LOG_ERR, "%s\n", "chdir");
		exit(EXIT_FAILURE);
	}
	umask(0);
	close(STDIN_FILENO);  // close standard input file descriptor
	close(STDOUT_FILENO); // close standard output file descriptor
	close(STDERR_FILENO); // close standard error file descriptor

	signal(SIGHUP,signal_handler); /* catch hangup signal */
	signal(SIGTERM,signal_handler); /* catch kill signal */
    signal(SIGUSR1,signal_handler); /* catch user signal */

	len = strlen(ctime(&timebuf));
	while (1) {
		char *buf = (char *)malloc(sizeof(char) + len + 1);
		if (buf == NULL) {
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		if ((fd = open("/var/log/daemons.log",	O_CREAT | O_WRONLY | O_APPEND, 0600)) < 0) {
			perror("open");
			exit(EXIT_FAILURE);
		}
		time((time_t*)&timebuf);
		strncpy(buf, ctime(&timebuf), len + 1);
		write(fd, buf, len + 1);
		close(fd);
		sleep(15);
	}
exit(EXIT_SUCCESS);		
}
