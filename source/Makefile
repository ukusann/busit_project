CC = g++ 
KDIR := ../header
DEPS = ../execute/

output: CDaemons.o daemons_main.o CPoint.o CNode.o CRoute.o CBusStop.o CMap.o main.o
	$(CC) -g -I $(KDIR) $(DEPS)CPoint.o $(DEPS)CNode.o $(DEPS)CRoute.o $(DEPS)CBusStop.o $(DEPS)CMap.o $(DEPS)main.o -o $(DEPS)busit.elf
	$(CC) -g -I $(KDIR) $(DEPS)CDaemons.o $(DEPS)daemons_main.o -o $(DEPS)daemon.elf

%.o: %.cpp
	$(CC) -g -c -I $(KDIR) $< -o $(DEPS)$@ 

clean:
	rm $(DEPS)*.o $(DEPS)*.elf

run:
	sudo ./$(DEPS)busit.elf

run_daemon:
	sudo ./$(DEPS)daemon.elf
