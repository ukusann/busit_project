CC = g++ 
KDIR := ../header
DEPS = ../execute/

output: CPoint.o CBusStop.o CNode.o CMap.o main.o
	$(CC) -I $(KDIR) $(DEPS)CPoint.o $(DEPS)CBusStop $(DEPS)CNode.o $(DEPS)CMap.o $(DEPS)main.o -o $(DEPS)busit.elf

%.o: %.cpp
	$(CC) -c -I $(KDIR) $< -o $(DEPS)$@ 

clean:
	rm $(DEPS)*.o $(DEPS)busit.elf

run:
	./$(DEPS)busit.elf
