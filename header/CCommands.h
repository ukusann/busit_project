#ifndef __CCommands__
#define __CCommands__

#define INIT_CMD  12
#define ERROR_CMD  0


#include <string>
#include <future>

bool initCmd();
bool inputCmd(std::future<std::string> &buffer);
#endif /*__cmd__*/