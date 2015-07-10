#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
using namespace std;

const string HELP_STR = "\n" 
			"***************************************************\n" 
			"* sdb is a simple student and course mgmt system  *\n"
			"***************************************************\n"
			"\nusage:\n"
			"\n\tsdb, sdb help: prints this help message"
			"\n\tsdb lss: lists all students"
			"\n\tsdb lss 'courseid': lists all students in course"
			"\n\tsdb adds 'firstname' 'surname' 'age' 'address':"
			"\n\t\tadds a student to the system"
			"\n\tsdb lsc: lists all courses"
			"\n\tsdb lsc 'studentid' lists a students courses"
			"\n\tsdb addc 'name' 'description' 'period' 'lecturer'"
			"\n\t\tadds a course to the system"
			"\n\tenrol 'studentid' 'courseid':"
			"\n\t\tenrols a student into a course\n";

int main(int argc, char* argv[]) {
	if(argc > 1 && strcmp(argv[1], "lss") == 0) {
		cout << "list all students" << endl;
		return 0;
	}	
	if(argc > 1 && strcmp(argv[1], "adds") == 0) {
		cout << "add a student" << endl;
		return 0;
	}
	if(argc > 1 && strcmp(argv[1], "lsc") == 0) {
		cout << "lists all courses" << endl;
		return 0;
	}
	if(argc > 1 && strcmp(argv[1], "addc") == 0) {
		cout << "adds a course" << endl;
		return 0;
	}
	if(argc > 1 && strcmp(argv[1], "enrol") == 0) {
		cout << "enrols a student" << endl;
		return 0;
	}
	
	cout << HELP_STR << endl;	
	return 0;
}
		
