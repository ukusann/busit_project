#intel compiler
CC = g++ 

#raspi compiler
#CC = /home/matheus/buildroot/buildroot-2021.08/output/host/bin/aarch64-linux-g++
KDIR := ../header  
KDIR_COMP 	 :=	/home/matheus/buildroot/buildroot-2021.08/output/build/linux-custom
KDIR_SERVER	 := ../server/FastCGI.com-master/original_snapshot/fcgi-2.4.1-SNAP-0910052249/include/
KDIR_SERVER2 := ../server/FastCGI.com-master/original_snapshot/fcgi-2.4.1-SNAP-0910052249/
DEPS = ../execute/

#===========================================================
#===========================================================
# ***********Beginning of Executable creation: *************

output: threads.o CPoint.o CNode.o CMap.o CRoute.o CGenerateRoute.o			\
		CBusStop.o CBus.o CCommands.o busit.o CDaemons.elf


	#TODO ******busit.elf creation******
		$(CC) -g -I $(KDIR) $(DEPS)CPoint.o $(DEPS)CNode.o $(DEPS)CMap.o 		\
	$(DEPS)CRoute.o $(DEPS)CGenerateRoute.o $(DEPS)CBusStop.o $(DEPS)CBus.o \
	$(DEPS)CCommands.o $(DEPS)busit.o -o $(DEPS)busit.elf

	#TODO ******server.elf creation*****
	mv $(DEPS)CDaemons.elf $(DEPS)server.elf

	#TODO ******shutdownServer.elf creation*****
	$(CC) -g -I $(KDIR) $(DEPS)threads.o 					\
	-o $(DEPS)shutdownServer.elf

# ***********End of Executable creation: *******************
#===========================================================
#===========================================================
# ***********Beginning of obj creation: ********************
CDaemons.elf: CDaemons.cpp
	$(CC) -g -I $(KDIR) CServer.cpp ffunc.c -L/usr/local/include -lfcgi -pthread -ldl -rdynamic -I $(KDIR_SERVER) -I $(KDIR_SERVER2) $< -o $(DEPS)$@ 


%.o: %.cpp
	$(CC) -g -c -I $(KDIR) $< -o $(DEPS)$@ 
# ***********End of obj creation: **************************
#===========================================================
#===========================================================
# ***********Beginning of make commands: *******************

clean: # 'make clean' removes all files in the executable folder
	rm $(DEPS)*.o $(DEPS)*.elf

busit: # 'make busit' executes busit.elf
	sudo ./$(DEPS)busit.elf


shutdownServer: # 'make shutdownServer' executes shutdownServer.elf
	sudo ./$(DEPS)shutdownServer.elf

server: # 'make server' executes server.elf
	sudo ./$(DEPS)server.elf

default: help

.PHONY: help 

help: # 'make help' Shows help for each of the Makefile commands.
	@grep -E '^[a-zA-Z0-9 -]+:.*#'  Makefile | sort | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done

# ***********End of make commands: *************************
#===========================================================
#===========================================================
