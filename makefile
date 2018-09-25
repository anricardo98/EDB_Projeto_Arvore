#Makefile for "tabela_dispersao" C++ application
#Created by Andre 12/09/2018

PROG = arvore
CC = g++
CPPFLAGS = -O0 -g -W -Wall -pedantic -std=c++11
OBJS = main.o

$(PROG): $(OBJS)
	$(CC) $(OBJS) -o $(PROG)

main.o: 
	 $(CC) $(CPPFLAGS) -c main.cpp

clean:
	rm -f *.o arvore