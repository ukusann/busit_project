CC = g++ 
KDIR := ../header
DEPS = ../execute/

output: CPoint.o CNode.o CRoute.o CBusStop.o CMap.o CGenerateRoute.o main.o
	$(CC) -I $(KDIR) $(DEPS)CPoint.o $(DEPS)CNode.o $(DEPS)CRoute.o $(DEPS)CBusStop.o $(DEPS)CMap.o $(DEPS)CGenerateRoute.o $(DEPS)main.o -o $(DEPS)busit.elf

%.o: %.cpp
	$(CC) -c -I $(KDIR) $< -o $(DEPS)$@ 

clean:
	rm $(DEPS)*.o $(DEPS)busit.elf

run:
	./$(DEPS)busit.elf
