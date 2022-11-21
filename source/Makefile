CC = g++ 
DEPS = ../execute/

output: main.o CNode.o CPoint.o
	$(CC) $(DEPS)main.o $(DEPS)CNode.o $(DEPS)CPoint.o -o $(DEPS)busit

main.o: main.cpp
	$(CC) -c main.cpp -o $(DEPS)main.o

CPoint.o: CPoint.cpp CPoint.h
	$(CC) -c CPoint.cpp -o $(DEPS)CPoint.o


CNode.o: CNode.cpp CNode.h
	$(CC) -c CNode.cpp -o $(DEPS)CNode.o

clean:
	rm *.o output

run:
	./$(DEPS)busit
