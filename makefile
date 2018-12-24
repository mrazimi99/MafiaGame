CC = g++
CCFLAGS = -c

all: run

run: Game.o Role.o Room.o Person.o Mafia.o GodFather.o Silencer.o Villager.o Doctor.o Detective.o RouinTan.o Joker.o MyException.o main.o
	$(CC) Game.o Role.o Room.o Person.o Mafia.o GodFather.o Silencer.o Villager.o Doctor.o Detective.o RouinTan.o Joker.o MyException.o main.o -o run.out

Game.o: Game.cpp Game.hpp Role.hpp Room.hpp Person.hpp Mafia.hpp GodFather.hpp Silencer.hpp Villager.hpp Doctor.hpp Detective.hpp RouinTan.hpp Joker.hpp MyException.hpp
	$(CC) $(CCFLAGS) Game.cpp

Role.o: Role.cpp Role.hpp
	$(CC) $(CCFLAGS) Role.cpp

Room.o: Room.cpp Room.hpp Role.hpp Person.hpp Mafia.hpp GodFather.hpp Silencer.hpp Villager.hpp Doctor.hpp Detective.hpp RouinTan.hpp Joker.hpp MyException.hpp
	$(CC) $(CCFLAGS) Room.cpp

Person.o: Person.cpp Person.hpp MyException.hpp
	$(CC) $(CCFLAGS) Person.cpp

Mafia.o: Mafia.cpp Mafia.hpp Person.hpp MyException.hpp
	$(CC) $(CCFLAGS) Mafia.cpp

GodFather.o: GodFather.cpp GodFather.hpp Mafia.hpp Person.hpp MyException.hpp
	$(CC) $(CCFLAGS) GodFather.cpp

Silencer.o: Silencer.cpp Silencer.hpp Mafia.hpp Person.hpp MyException.hpp
	$(CC) $(CCFLAGS) Silencer.cpp

Villager.o: Villager.cpp Villager.hpp Person.hpp MyException.hpp
	$(CC) $(CCFLAGS) Villager.cpp

Doctor.o: Doctor.cpp Doctor.hpp Villager.hpp Person.hpp MyException.hpp
	$(CC) $(CCFLAGS) Doctor.cpp

Detective.o: Detective.cpp Detective.hpp Villager.hpp Person.hpp MyException.hpp
	$(CC) $(CCFLAGS) Detective.cpp

RouinTan.o: RouinTan.cpp RouinTan.hpp Villager.hpp Person.hpp MyException.hpp
	$(CC) $(CCFLAGS) RouinTan.cpp

Joker.o: Joker.cpp Joker.hpp Person.hpp MyException.hpp
	$(CC) $(CCFLAGS) Joker.cpp

MyException.o: MyException.cpp MyException.hpp
	$(CC) $(CCFLAGS) MyException.cpp

main.o: main.cpp Game.hpp Role.hpp Room.hpp Person.hpp Mafia.hpp GodFather.hpp Silencer.hpp Villager.hpp Doctor.hpp Detective.hpp RouinTan.hpp Joker.hpp MyException.hpp
	$(CC) $(CCFLAGS) main.cpp

clean:
	rm -r *.o *~