CC = g++ 
KDIR := ../header
DEPS = ../execute/

output: main.o CMap.o CNode.o CPoint.o
	$(CC) -I $(KDIR) $(DEPS)main.o  $(DEPS)CMap.o $(DEPS)CNode.o $(DEPS)CPoint.o -o $(DEPS)busit.elf

main.o: main.cpp
	$(CC) -c -I $(KDIR) main.cpp -o $(DEPS)main.o

CPoint.o: CPoint.cpp
	$(CC) -c -I $(KDIR) CPoint.cpp -o $(DEPS)CPoint.o


CNode.o: CNode.cpp
	$(CC) -c -I $(KDIR) CNode.cpp -o $(DEPS)CNode.o

CMap.o: CMap.cpp
	$(CC) -c -I $(KDIR) CMap.cpp -o $(DEPS)CMap.o

clean:
	rm $(DEPS)*.o $(DEPS)busit.elf

run:
	./$(DEPS)busit.elf
