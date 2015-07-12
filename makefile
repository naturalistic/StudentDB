all: sqlite3.o repository.o student.o
	g++ sdb.cpp student.o repository.o sqlite3.o -lpthread -ldl -o sdb
student.o: student.cpp
	g++ -c student.cpp
repository.o: repository.cpp
	g++ -c repository.cpp
sqlite3.o: sqlite3.c
	gcc -c sqlite3.c
