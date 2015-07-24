#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdexcept>
#include "course.h"
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
			"\n\tsdb lss 'studentid': prints the student with that id"
			"\n\tsdb adds 'firstname' 'surname' 'birth date' 'address':"
			"\n\t\tadds a student to the system"
			"\n\tsdb lsc: lists all courses"
			"\n\tsdb lsc 'courseid': prints the course with that id"
			"\n\tsdb addc 'name' 'description' 'period' 'lecturer'"
			"\n\t\tadds a course to the system"
			"\n\tenrol 'studentid' 'courseid':"
			"\n\t\tenrols a student into a course"
			"\n\tsdb lssc 'studentid' prints a students courses"
                        "\n\tsdb lscs 'courseid' prints all students in a course\n";

const string HELP_LSS_STR =	"\nIncorrect usage of 'lss' command\n\n"
				"Usage: \n"
				"\n\tsdb lss: lists all students"
				"\n\tsdb lss 'studentid': prints the student with that id\n"
				"\tnote that studentid must be a positive integer\n";

const string HELP_LSC_STR =	"\nIncorrect usage of 'lsc' command\n\n"
				"Usage: \n"
				"\n\tsdb lsc: lists all courses"
				"\n\tsdb lsc 'courseid': prints the course with that id"
				"\n\tnote that courseid must be a positive integer\n";

const string HELP_ADDS_STR =	"\nIncorrect usage of 'adds' command\n\n"
				"Usage: \n"
				"\tsdb adds 'firstname' 'surname' 'birth date' 'address'\n";

const string HELP_ADDC_STR = 	"\nIncorrect usage of 'addc' command\n\n"
				"Usage:\n"
				"\tsdb addc 'name' 'period' 'description' 'lecturer'\n";	

const string HELP_ENROL_STR =	"\nIncorrect usage of 'enrol' command\n\n"
				"Usage: \n"
				"\tsdb enrol 'studentid' 'courseid'\n"
				"\tnote that both studentId and courseId must be\n"
				"\tpositive integers\n\n";

const string HELP_LSSC_STR =	"\nIncorrect usage of 'lssc' command\n\n"
				"Usage:\n"
				"\tsdb lssc 'studentid'\n"
				"\tnote that student id must be a positive integer\n";

const string HELP_LSCS_STR =	"\nIncorrect usage of 'lscs' command\n\n"
				"Usage:\n"
				"\tsdb lscs 'courseid'\n"
				"\tnote that course id must be a positive integer\n";

Repository repo; // global repo instance

void listStudents(int argc, char* argv[]) {
	vector<Student> sv;
	if(argc == 2) {
		if(!repo.getStudents(sv)) {
			cerr << "There was an error getting students!" << endl;
			return;
		}
	} else {
		int studentId;
		bool validId = true;
		try {
			string::size_type sz;
			studentId = stoi(argv[2], &sz);
			validId = sz == strlen(argv[2]);
		} catch (const invalid_argument& ia) {
			validId = false;
		}
		if(!validId) {
			cout << HELP_LSS_STR << endl; 
			return;
		}
		if(!repo.getStudents(sv, studentId)) {
			cerr << "There was an error getting students!" << endl; 
			return;
		}
	}
	for(vector<Student>::iterator it = sv.begin(); it != sv.end(); ++it) {
		it->print();
	}
}

void addStudent(int argc, char* argv[]) {
	if(argc == 6) {
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

void listCourses(int argc, char* argv[]) {
        vector<Course> cv;
	if(argc == 2) {
        	if(!repo.getCourses(cv)) {
               		cerr << "There was a error getting courses!" << endl;
                	return;
        	}
	} else {
		int courseId;
		bool validId = true;
		try {
			string::size_type sz;
			courseId = stoi(argv[2], &sz);
			validId = sz == strlen(argv[2]);
		} catch (const invalid_argument& ia) {
			validId = false;
		}
		if(!validId) {
			cout << HELP_LSC_STR << endl; 
			return;
		}
		if(!repo.getCourses(cv, courseId)) {
			cerr << "There was an error getting courses!" << endl; 
			return;
		}
	}
        for(vector<Course>::iterator it = cv.begin(); it != cv.end(); ++it) {
                it->print();
        
	}
}

void addCourse(int argc, char* argv[]) {
        if(argc == 6) {
                Course c (0, argv[2], argv[3], argv[4], argv[5]);
                if(!repo.insertCourse(c)) {
                        cerr << "There was an error while adding course to the system!";
                        return;
               }
                cout << "'" << c.getName() << "' Added" << endl;
                return;
        }
        cout << HELP_ADDC_STR << endl;
}

void enrolStudent(int argc, char* argv[]) {
	if(argc == 4) {
		try {
			string::size_type sz1;
			string::size_type sz2;
			int studentId = stoi(argv[2], &sz1);
			int courseId = stoi(argv[3], &sz2);
			bool validArg = sz1 == strlen(argv[2]) && sz2 == strlen(argv[3]);
			if(validArg && repo.enrolStudent(studentId, courseId)) {
				cout << "COMPLETEED";
				return;
			}
		
		} catch (const invalid_argument& ia) {
			// Do nothing
		}
	}
	cout << HELP_ENROL_STR << endl;
}

void listStudentCourses(int argc, char* argv[]) {
	if(argc == 3) {
		vector<Course> cv;
		int studentId;
		bool validId = true;
		try {
			string::size_type sz;
			studentId = stoi(argv[2], &sz);
			validId = sz == strlen(argv[2]);
		} catch (const invalid_argument& ia) {
			validId = false;
		}
		if(!validId) {
			cout << HELP_LSSC_STR << endl; 
			return;
		}
		if(!repo.getStudentCourses(cv, studentId)) {
			cerr << "There was an error getting the students courses!" << endl; 
			return;
		}
		for(vector<Course>::iterator it = cv.begin(); it != cv.end(); ++it) {
                	it->print();
		}
	} else {
		cout << HELP_LSSC_STR << endl;
	}
}

void listCourseStudents(int argc, char* argv[]) {
	if(argc == 3) {
		vector<Student> sv;
		int courseId;
		bool validId = true;
		try {
			string::size_type sz;
			courseId = stoi(argv[2], &sz);
			validId = sz == strlen(argv[2]);
		} catch (const invalid_argument& ia) {
			validId = false;
		}
		if(!validId) {
			cout << HELP_LSCS_STR << endl; 
			return;
		}
		if(!repo.getCourseStudents(sv, courseId)) {
			cerr << "There was an error getting the courses students!" << endl; 
			return;
		}
		for(vector<Student>::iterator it = sv.begin(); it != sv.end(); ++it) {
                	it->print();
		}
	} else {
		cout << HELP_LSCS_STR << endl;
	}
}

// Redirect sdb commands to dedicated functions
int main(int argc, char* argv[]) {
	if(!repo.init()) {
		return 1;
	}
	if(argc > 1 && strcmp(argv[1], "lss") == 0) {
		listStudents(argc, argv);	
		return 0;
	}	
	if(argc > 1 && strcmp(argv[1], "adds") == 0) {
		addStudent(argc, argv);
		return 0;
	}
	if(argc > 1 && strcmp(argv[1], "lsc") == 0) {
		listCourses(argc, argv);
		return 0;
	}
	if(argc > 1 && strcmp(argv[1], "addc") == 0) {
		addCourse(argc, argv);
		return 0;
	}
	if(argc > 1 && strcmp(argv[1], "enrol") == 0) {
		enrolStudent(argc, argv);
		return 0;
	}
	if(argc > 1 && strcmp(argv[1], "lssc") == 0) {
		listStudentCourses(argc, argv);
		return 0;
	}
	if(argc > 1 && strcmp(argv[1], "lscs") == 0) {
		listCourseStudents(argc, argv);
		return 0;
	}
	cout << HELP_STR << endl;	
	return 0;
}
		
