CC = g++ 
KDIR := ../header
DEPS = ../execute/
OBJS = CNode.o CPoint.o main.o

output: CNode.o CPoint.o main.o
	$(CC) -I $(KDIR) $(DEPS)CNode.o $(DEPS)CPoint.o $(DEPS)main.o -o $(DEPS)busit.elf

%.o: %.cpp
	$(CC) -c -I $(KDIR) $< -o $(DEPS)$@ 

clean:
	rm $(DEPS)*.o $(DEPS)busit.elf

run:
	./$(DEPS)busit.elf





