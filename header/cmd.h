#ifndef __cmd__
#define __cmd__

#define INIT_CMD  12
#define ERROR_CMD  0

bool initCmd();
bool inputCmd( const unsigned char* buffer);

#endif /*__cmd__*/