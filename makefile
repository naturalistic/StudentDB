CPPFLAGS = -std=c++11 
LDLIBS = -lpthread -ldl
all: sqlite3.o repository.o student.o course.o
	g++ $(CPPFLAGS) sdb.cpp course.o student.o repository.o sqlite3.o -o sdb $(LDLIBS)
course.o: course.cpp
	g++ $(CPPFLAGS) -c course.cpp
student.o: student.cpp
	g++ $(CPPFLAGS) -c student.cpp
repository.o: repository.cpp
	g++ $(CPPFLAGS) -c repository.cpp
sqlite3.o: sqlite3.c
	gcc -c sqlite3.c
