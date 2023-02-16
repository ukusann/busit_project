/** *****************************************************************************************************************
 * Threads:
 *  PMainSystem;
 *  PCmd
********************************************************************************************************************/

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/syslog.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <thread>
#include <mutex>
#include <mqueue.h>	
#include <time.h>
#include "CCommands.h"
using namespace std;


// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
// Signal:
#define SIGTX 44
#define REGISTER_UAPP _IO('R', 'g')

// Device Driver:
#define UART_FILE "/dev/cmdfile"
#define LED_FILE  "/dev/ledfile"

int fuart;      // uart file 
int fleds;      // gpio file

//Message Queue:
#define MSG_QUEUE_NAME  "/errorMsg"
#define MSG_QUEUE_MAX_LEN 10000
 
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

// ==================================================================================================================
// ==================================================================================================================
/**
 * CALLBACKS
*/
// Signals:
void signalhandler (int sig){
    switch(sig) {
		case SIGTX:
			syslog(LOG_INFO,"Busit console signal catched");
			break;
    }
  //  flag_sig = 1;
}

// ==================================================================================================================
// ==================================================================================================================

// ==================================================================================================================
// ==================================================================================================================

// ==================================================================================================================
// ==================================================================================================================
/**
 * ERROR Condition thread: PERROR
*/
string PError(){
    string err_msg;

    return err_msg;
}
// ==================================================================================================================
// ==================================================================================================================

// ==================================================================================================================
// ==================================================================================================================

// ==================================================================================================================
// ==================================================================================================================
/**
 * CMD Thread: PERROR
*/


// ==================================================================================================================
// ==================================================================================================================

// ==================================================================================================================
// ==================================================================================================================

// ==================================================================================================================
// ==================================================================================================================
/**
 * Main Thread: Close Functions:
*/
void closeUartDD(){
        close(fuart);
        system("rmmod /dev/uartmodule");        // removes the DD 
        system("rm /dev/uartmodule.ko");        // deletes the .ko file
}
void closeLedDD(){
        close(fleds);
        system("rmmod /dev/gpiomodule");        // removes the DD 
        system("rm /dev/gpiomodule.ko");        // deletes the .ko file
}
void closeServer(){

}
void closeI2C(){
    
}
//  ---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---
//  ---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---
/**
 * Main Thread: Init Busit
*/

bool initBusit(){

    /* Device Drivers */
        // Uart                                 
/*        system("scp uartmodule.ko /dev/");          // copies the .ko to the /dev/
        system("chmod 666 /dev/uartmodule.ko");     // all users can read and write but cannot execute the file
        system("insmod /dev/uartmodule.ko");        // insert the DD
        fuart = open(UART_FILE, O_RDONLY);          // opens only to read 
        if (fuart < 0)  {goto DD_UART_INIT_ERROR;}  // fails to open the file
*/
        // GPIO - leds
/*        system("scp gpiomodule.ko /dev/");          // copies the .ko to the /dev/
        system("chmod 666 /dev/gpiomodule.ko");     // all users can read and write but cannot execute the file
        system("insmod /dev/gpiomodule.ko");        // insert the DD
        fleds = open(LED_FILE, O_WRONLY);           // opens only to write
        if (fleds < 0)  {goto DD_GPIO_INIT_ERROR;}  // fails to open the file
*/
    /* Server */
    
    /* I2C */


    /* Signal */
        signal(SIGTX, signalhandler);
        printf("Process PID: %d\n", getpid());

    /* Threads */
        if (initCmd())
            return true;

// I2C_INIT_ERROR:
//     closeI2C();
// SERVER_INIT_ERROR:
//     closeServer();
// DD_GPIO_INIT_ERROR:
//     closeLedDD();
// DD_UART_INIT_ERROR:
//     closeUartDD();
    
    return false;
}

//  ---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---
//  ---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---
/**
 * Main Thread: MainSystem
*/
void MainSystem(){
    /****Message Queue****/
    mqd_t msgq_id;
    char msgcontent[MSG_QUEUE_MAX_LEN];
    int message_status;
    unsigned int sender;
    const struct timespec t{0,5};
    const struct timespec *time{&t};
    //=====================
    bool error = false;
    while(error == false)
    {
        msgq_id = mq_open(MSG_QUEUE_NAME, O_CREAT | O_RDWR, 0666, NULL); // opens an existing message queue to read

        /* checks if message queue could be opened*/
        if (msgq_id == (mqd_t)-1) 
        {
            perror("In mq_open()");
            exit(1);
        }

        message_status = mq_timedreceive(msgq_id, msgcontent, MSG_QUEUE_MAX_LEN, &sender,  time); // gets the message from message queue

        /*checks if message queue could be read*/
        if (message_status != -1) 
        {
            printf("Received message (%d bytes) from %d: %s\n", message_status, sender, msgcontent);
            mq_close(msgq_id);
            if (mq_unlink(MSG_QUEUE_NAME) == -1)
                perror("Removing queue error");
        }

        mq_close(msgq_id);

        promise<string> command;                                                                    // creates a promise
        future<string> getCommand_future = command.get_future();                                    // sets promise to future
        future<bool> inputCommand_future = async(launch::async, inputCmd, ref(getCommand_future));  // creates a thread with the future variable
        string input;                                                                                
        getline(cin, input);            // gets input from console

        /* checks if the string sent is an exit command */
        if(input.compare("exit") == 0)                                 
        {
            command.set_value("");      // fulfills promise with null string
            error = true;               // ends thread
        }
        else
        {
            command.set_value(input);               // fulfills promise with input value
            if (inputCommand_future.get() == false) // checks if command is a valid command
                cout << "Error in command!" << endl; 
        }
    }
}
//  ---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---
//  ---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---__---

int main(){
//  - - - - - - - - - - - - - - - - - - - - - -
// Open Condition:
    if (initBusit())
//  - - - - - - - - - - - - - - - - - - - - - -
        // Main Sys Thread (main)
        MainSystem();
//  - - - - - - - - - - - - - - - - - - - - - -
// Close Condition:
    
    /* Device Drivers */
        // Uart            
        //closeUartDD();
        
        // GPIO - leds
        //closeLedDD();

//  - - - - - - - - - - - - - - - - - - - - - -
    return 0;
}

