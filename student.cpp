#include <iostream>
#include "student.h"

using namespace std;
namespace sdb {
Student::Student() { }

// Student Constructor
Student::Student(int _id, string _firstName, string _surname, string _dob, string _address) {
	id = _id;
	firstName = _firstName;
	surname = _surname;
	dob = _dob;
	address = _address;
}


void Student::print() {
	cout << "ID: " << id << ", Name: " << firstName << " " << surname << 
		", DOB: " << dob << " " << ", Address: " << address << endl;
}


}

