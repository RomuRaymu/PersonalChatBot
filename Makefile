main.out: main.o ChatBot.o Calculator.o Alarm.o Daters.o MineMap.o MineSweeper.o Schedulers.o Calendar.o DirectoryManager.o
	g++ main.o ChatBot.o Calculator.o Alarm.o Daters.o MineMap.o MineSweeper.o Schedulers.o Calendar.o DirectoryManager.o -o main.out

ChatBot.o : ChatBot.cpp
	g++ ChatBot.cpp -c -o ChatBot.o

Calculator.o : Calculator.cpp
	g++ Calculator.cpp -c -o Calculator.o

Alarm.o : Alarm.cpp
	g++ Alarm.cpp -c -o Alarm.o

Daters.o : Daters.cpp
	g++ Daters.cpp -c -o Daters.o

MineMap.o : MineMap.cpp
	g++ MineMap.cpp -c -o MineMap.o

MineSweeper.o : MineSweeper.cpp
	g++ MineSweeper.cpp -c -o MineSweeper.o

Schedulers.o : Schedulers.cpp
	g++ Schedulers.cpp -c -o Schedulers.o

Calendar.o : Calendar.cpp
	g++ Calendar.cpp -c -o Calendar.o

DriectoryManager.cpp : DirectoryManager.cpp
	g++ DirectoryManager.cpp -c -o DirectoryManager.o