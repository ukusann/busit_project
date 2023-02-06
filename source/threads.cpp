/*#include "CPoint.h"
#include "CNode.h"
#include "CBusStop.h"
#include "CRoute.h"
#include "CMap.h"
*/


#include <cstring>
#include <mqueue.h>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <signal.h>
#include <sys/syslog.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> 
#include <cstdlib>
#include <pthread.h>
#include <future>         // threads future
#include <sched.h>
#include <errno.h>
#include <string.h>

#define QUEUE_NAME 		"/queue1"

#define MAX_MSG_LEN 	40

using namespace std;

/*  BEGIN OF GLOBAL VARIBLES */

	// Device Driver
	#define UART_DD 
	#define GPIO_DD 
	int fuart;  // uart
	int fgpio;  // gpio

/*  END OF GLOBAL VARIBLES */


void signalHandler(int sig)
{
	    switch(sig) {
		case SIGHUP:
			syslog(LOG_INFO,"Hangup signal catched");
			break;

        case SIGUSR1:
            syslog(LOG_INFO,"User signal catched");
			raise(SIGTERM);
            break;

		case SIGTERM:
			syslog(LOG_INFO,"Terminate signal catched");
			exit(0);
			break;
	}
}



void CheckFail(int status)
{
	if(status)
	{
		if(status == EPERM)
			fprintf(stderr, "pthread_create() got EPERM\n");
		else if(status == EINVAL)
      			fprintf(stderr, "pthread_create() got EINVAL\n");
    		else
      			fprintf(stderr, "pthread_create() got neither EPERM nor EINVAL\n");

		fprintf(stderr, "pthread_create() got error %d\n", status);
		errno = status;
		perror("pthread_create()");
		exit(1);
  	}
}


void *thread1_routine (void *arg)
{
	int my_policy;
	struct sched_param my_param;
	
	pthread_getschedparam (pthread_self (), &my_policy, &my_param);
	printf ("thread1_routine running at %s/%d\n",
		(my_policy == SCHED_FIFO ? "FIFO"
		: (my_policy == SCHED_RR ? "RR"
		: (my_policy == SCHED_OTHER ? "OTHER"
		: "unknown"))),my_param.sched_priority);
	
    //? *****begin code*****
    
    //? *****end code*****
	return NULL;
}

void *pMainSystem (void *arg)
{
	int my_policy;
	struct sched_param my_param;
	
	pthread_getschedparam (pthread_self (), &my_policy, &my_param);
	printf ("thread2_routine running at %s/%d\n",
		(my_policy == SCHED_FIFO ? "FIFO"
		: (my_policy == SCHED_RR ? "RR"
		: (my_policy == SCHED_OTHER ? "OTHER"
		: "unknown"))),my_param.sched_priority);
	
	//? *****begin code*****
	
	pid_t pid;
    signal(SIGUSR1, signalHandler); // Register signal handler
    signal(SIGTERM, signalHandler); // Register signal handler
    pid = getpid();      //Process ID of itself
     printf("Busit PID: %d\n", pid);
     
     int total_length = 1024; 

     char line[total_length];
     FILE * command = popen("pidof -s server.elf","r");

     fgets(line,total_length,command);

     pid_t pid2 = strtoul(line,NULL,10);
     pclose(command);
     
     printf("Daemon PID: %d\n", pid2);
     
     //kill(pid2, SIGUSR1);        // Send SIGUSR1 to daemon

    kill(pid2, SIGTERM);

    kill(pid, SIGTERM);

	//? *****end code*****
	return NULL;
}


void SetupThread(int prio,pthread_attr_t *pthread_attr,struct sched_param *pthread_param)
{
	int rr_min_priority, rr_max_priority;

	pthread_attr_setschedpolicy (pthread_attr, SCHED_RR); //step 6 now is step 2
	rr_min_priority = sched_get_priority_min (SCHED_RR);
	rr_max_priority = sched_get_priority_max (SCHED_RR);
	pthread_param->sched_priority = prio;
	
	printf ("SCHED_RR priority range is %d to %d: using %d\n",rr_min_priority,rr_max_priority,pthread_param->sched_priority);

	pthread_attr_setschedparam (pthread_attr, pthread_param);

	//step 5 is eliminated here
}

// ============================================================================
/*  						  INIT GENERAL SYSTEM 						 	 */
//_____________________________________________________________________________	



int main (int argc, char *argv[])
{
    //? BEGIN CODE
    void *t_status_1, *t_status_2;
    //? END CODE
	int thread_policy;
	pthread_t thread1_id, thread2_id;

	pthread_attr_t thread_attr;
	struct sched_param thread_param;
	

	pthread_attr_init (&thread_attr);
	pthread_attr_getschedpolicy (&thread_attr, &thread_policy);
	pthread_attr_getschedparam (&thread_attr, &thread_param);
	
	/*printf (
		"Default policy is %s, priority is %d\n",
		(thread_policy == SCHED_FIFO ? "FIFO"
		: (thread_policy == SCHED_RR ? "RR"
		: (thread_policy == SCHED_OTHER ? "OTHER"
		: "unknown"))),thread_param.sched_priority);

	SetupThread(25,&thread_attr,&thread_param);
	*/
	printf ("Creating thread at RR/%d\n",thread_param.sched_priority);
	pthread_attr_setinheritsched (&thread_attr, PTHREAD_EXPLICIT_SCHED);
	int status_2 = pthread_create (&thread2_id, &thread_attr, pMainSystem, NULL);

	SetupThread(15,&thread_attr,&thread_param);
	
	printf ("Creating thread at RR/%d\n",thread_param.sched_priority);
	pthread_attr_setinheritsched (&thread_attr, PTHREAD_EXPLICIT_SCHED);
	int status_1 = pthread_create (&thread1_id, &thread_attr, thread1_routine, NULL);


	CheckFail(status_2);
	CheckFail(status_1);
	
	pthread_join (thread2_id, &t_status_2);
	pthread_join (thread1_id, &t_status_1);

    if(t_status_1 == (void *)-1 || t_status_2 == (void *)-1)
        cout << "Error! End of program..." << endl;
    
    else
        cout << "Sucess! End of program!" << endl;
    
    pthread_exit(NULL);
    return 0;
}















