CC = g++
CCFLAGS = -c

all: run

run: Person.o Mafia.o Vilager.o main.o
	$(CC) Person.o Mafia.o Vilager.o main.o -o run.out

Person.o: Person.cpp Person.hpp Mafia.hpp Vilager.hpp
	$(CC) $(CCFLAGS) Person.cpp

Mafia.o: Mafia.cpp Mafia.hpp Vilager.hpp Person.hpp
	$(CC) $(CCFLAGS) Mafia.cpp

Vilager.o: Vilager.cpp Vilager.hpp Person.hpp
	$(CC) $(CCFLAGS) Vilager.cpp

main.o: main.cpp Person.hpp Mafia.hpp Vilager.hpp
	$(CC) $(CCFLAGS) main.cpp

clean:
	rm -r *.o *~