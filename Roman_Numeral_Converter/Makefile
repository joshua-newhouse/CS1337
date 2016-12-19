PROG = RomNum
CC = g++
CFLAGS = -std=c++11 -pedantic-errors -O3
OBJS = RN.o FileHandler.o Parser.o Translator.o jlib.o list.o node.o

RomNum:	main.o $(OBJS)
	$(CC) $(CFLAGS) main.o $(OBJS) -o $(PROG)

debug:	main.o $(OBJS)
	$(CC) $(CFLAGS) main.o $(OBJS) -g -o Debug

driver: driver.cpp $(OBJS)
	$(CC) $(CFLAGS) driver.cpp $(OBJS) -g -o Debug

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

RN.o: RN.cpp
	$(CC) $(CFLAGS) -c RN.cpp

FileHandler.o: FileHandler.cpp
	$(CC) $(CFLAGS) -c FileHandler.cpp

Parser.o: Parser.cpp
	$(CC) $(CFLAGS) -c Parser.cpp

Translator.o: Translator.cpp
	$(CC) $(CFLAGS) -c Translator.cpp

jlib.o: jlib.cpp
	$(CC) $(CFLAGS) -c jlib.cpp

list.o: list.cpp
	$(CC) $(CFLAGS) -c list.cpp

node.o: node.cpp
	$(CC) $(CFLAGS) -c node.cpp

clean:
	-rm -rf *o $(PROG) Debug
