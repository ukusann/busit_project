CC = g++ 
KDIR := ../header  
DEPS = ../execute/

#===========================================================
#===========================================================
# ***********Beginning of Executable creation: *************

output: CDaemons.o daemons_main.o CPoint.o CNode.o CRoute.o CBusStop.o \
		CMap.o CGenerateRoute.o main.o

	#TODO ******busit.elf creation******
	$(CC) -g -I $(KDIR) $(DEPS)CPoint.o $(DEPS)CNode.o $(DEPS)CRoute.o \
	$(DEPS)CBusStop.o $(DEPS)CMap.o $(DEPS)CGenerateRoute.o $(DEPS)main.o \
	-o $(DEPS)busit.elf

	#TODO ******daemon.elf creation*****
	$(CC) -g -I $(KDIR) $(DEPS)CDaemons.o $(DEPS)daemons_main.o \
	-o $(DEPS)daemon.elf

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

# ***********End of make commands: *************************
#===========================================================
#===========================================================
