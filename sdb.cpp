#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include "student.h"
#include "repository.h"
using namespace std;
using namespace sdb;

const string HELP_STR = "\n" 
			"***************************************************\n" 
			"* sdb is a simple student and course mgmt system  *\n"
			"***************************************************\n"
			"\nusage:\n"
			"\n\tsdb, sdb help: prints this help message"
			"\n\tsdb lss: lists all students"
			"\n\tsdb lss 'courseid': lists all students in course"
			"\n\tsdb adds 'firstname' 'surname' 'birth date' 'address':"
			"\n\t\tadds a student to the system"
			"\n\tsdb lsc: lists all courses"
			"\n\tsdb lsc 'studentid' lists a students courses"
			"\n\tsdb addc 'name' 'description' 'period' 'lecturer'"
			"\n\t\tadds a course to the system"
			"\n\tenrol 'studentid' 'courseid':"
			"\n\t\tenrols a student into a course\n";

const string HELP_ADDS_STR =	"\n"
				"Incorrect usage of 'adds' command\n"
				"Usage: \n"
				"\tsdb adds 'firstname' 'surname' 'birth date' 'address':";

Repository repo; // global repo instance

void listStudents() {
	vector<Student> sv;
	if(!repo.getStudents(sv)) {
		cerr << "There was a error getting students!" << endl;
		return;
	}
	for(vector<Student>::iterator it = sv.begin(); it != sv.end(); ++it) {
		it->print();
	}
}

void addStudent(int argc, char* argv[]) {
	if(argc == 6) {
		// try parse first int.
		Student s (0, argv[2], argv[3], argv[4], argv[5]);
		if(!repo.insertStudent(s)) {
			cerr << "There was an error while adding student to the system!";
			return;
		}
		cout << "'" << s.getFirstName() << "' Added" << endl;
		return;
	}
	cout << HELP_ADDS_STR << endl;
}

// Redirect sdb commands to dedicated functions
int main(int argc, char* argv[]) {
	if(!repo.init()) {
		return 1;
	}
	if(argc > 1 && strcmp(argv[1], "lss") == 0) {
		listStudents();	
		return 0;
	}	
	if(argc > 1 && strcmp(argv[1], "adds") == 0) {
		addStudent(argc, argv);
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
		
