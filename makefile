all: sqlite3.o
	g++ sdb.cpp sqlite3.o -lpthread -ldl -o sdb

sqlite3.o: sqlite3.c
	gcc -c sqlite3.c




