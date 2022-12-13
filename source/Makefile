CC = g++ 
KDIR := ../header  
DEPS = ../execute/

#===========================================================
#===========================================================
# ***********Beginning of Executable creation: *************

output: threads.o CDaemons.o daemons_main.o CPoint.o CNode.o CMap.o 		\
	CRoute.o CGenerateRoute.o CBusStop.o main.o

	#TODO ******busit.elf creation******
	$(CC) -g -I $(KDIR) $(DEPS)CPoint.o $(DEPS)CNode.o $(DEPS)CMap.o 		\
	$(DEPS)CRoute.o $(DEPS)CGenerateRoute.o $(DEPS)CBusStop.o $(DEPS)main.o \
	-o $(DEPS)busit.elf

	#TODO ******daemon.elf creation*****
	$(CC) -g -I $(KDIR) $(DEPS)CDaemons.o $(DEPS)daemons_main.o				\
	-o $(DEPS)daemon.elf

	#TODO ******thread.elf creation*****
	$(CC) -g -I $(KDIR) $(DEPS)CDaemons.o $(DEPS)threads.o 					\
	-o $(DEPS)threads.elf

# ***********End of Executable creation: *******************
#===========================================================
#===========================================================
# ***********Beginning of obj creation: ********************

%.o: %.cpp
	$(CC) -g -c -I $(KDIR) $< -o $(DEPS)$@ 


# ***********End of obj creation: **************************
#===========================================================
#===========================================================
# ***********Beginning of make commands: *******************

#? 'make clean' removes all files in the executable folder
clean:
	rm $(DEPS)*.o $(DEPS)*.elf

#? 'make run' executes busit.elf
run:
	sudo ./$(DEPS)busit.elf

#? 'make run_daemon' executes daemon.elf
run_daemon:
	sudo ./$(DEPS)daemon.elf

#? 'make run_thread' executes threads.elf
run_thread:
	sudo ./$(DEPS)threads.elf

# ***********End of make commands: *************************
#===========================================================
#===========================================================
