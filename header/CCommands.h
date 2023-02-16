#ifndef __CCommands__
#define __CCommands__

#define INIT_CMD  12
#define ERROR_CMD  0


#include <string>
#include <future>

bool initCmd();
bool inputCmd(std::future<std::string> &buffer);
// put string with ok or error in message queue
// in main will read from message queue and launch error thread
// error thread will write the string; 
#endif /*__cmd__*/