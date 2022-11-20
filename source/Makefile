CC = g++
DEPS = ~/busit_project/header/CPoint.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

CPoint: main.o CPoint.o
	$(CC) -o CPoint main.o CPoint.o

