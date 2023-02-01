CC = g++ 
KDIR := ../header  
KDIR_SERVER	 := ../server_test/FastCGI.com-master/original_snapshot/fcgi-2.4.1-SNAP-0910052249/include/
KDIR_SERVER2 := ../server_testFastCGI.com-master/original_snapshot/fcgi-2.4.1-SNAP-0910052249/
DEPS = ../execute/

#===========================================================
#===========================================================
# ***********Beginning of Executable creation: *************

output: threads.o CDaemons.o daemons_main.o CPoint.o CNode.o CMap.o 		\
	CRoute.o CGenerateRoute.o CBusStop.o main.o CServer.elf

	#TODO ******busit.elf creation******
	$(CC) -g -I $(KDIR) $(DEPS)CPoint.o $(DEPS)CNode.o $(DEPS)CMap.o 		\
	$(DEPS)CRoute.o $(DEPS)CGenerateRoute.o $(DEPS)CBusStop.o 				\
	$(DEPS)cmd.o $(DEPS)busit.o -o $(DEPS)busit.elf

	#TODO ******daemon.elf creation*****
	$(CC) -g -I $(KDIR) $(DEPS)CDaemons.o $(DEPS)daemons_main.o				\
	-o $(DEPS)daemon.elf

	#TODO ******server.elf creation*****
	mv $(DEPS)CServer.elf $(DEPS)server.elf

	#TODO ******thread.elf creation*****
	$(CC) -g -I $(KDIR) $(DEPS)CDaemons.o $(DEPS)threads.o 					\
	-o $(DEPS)threads.elf

# ***********End of Executable creation: *******************
#===========================================================
#===========================================================
# ***********Beginning of obj creation: ********************
CServer.elf: CServer.cpp
	$(CC) -g ffunc.c -I $(KDIR) -L/usr/local/include -lfcgi -pthread -ldl -rdynamic -I $(KDIR_SERVER) -I $(KDIR_SERVER2) $< -o $(DEPS)$@ 


%.o: %.cpp
	$(CC) -g -c -I $(KDIR) $< -o $(DEPS)$@ 
# ***********End of obj creation: **************************
#===========================================================
#===========================================================
# ***********Beginning of make commands: *******************

clean: # 'make clean' removes all files in the executable folder
	rm $(DEPS)*.o $(DEPS)*.elf

run: # 'make run' executes busit.elf
	sudo ./$(DEPS)busit.elf

daemon: # 'make daemon' executes daemon.elf
	sudo ./$(DEPS)daemon.elf

thread: # 'make thread' executes threads.elf
	sudo ./$(DEPS)threads.elf

server: # 'make server' executes server.elf
	sudo ./$(DEPS)server.elf

default: help

.PHONY: help 

help: # 'make help' Show help for each of the Makefile commands.
	@grep -E '^[a-zA-Z0-9 -]+:.*#'  Makefile | sort | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done

# ***********End of make commands: *************************
#===========================================================
#===========================================================
