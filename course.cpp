#include <iostream>
#include "course.h"

using namespace std;
namespace sdb {

Course::Course() {}

// Course Constructor
Course::Course(int _id, string _name, string _period, string _desc, string _lecturer) {
        id = _id;
        name = _name;
	period = _period;
	description = _desc;
	lecturer = _lecturer;
}

void Course::print() {
        cout << "ID: " << id << ", Name: " << name << ", Period: " << period <<
                ", Description: " << description << ", Lecturer: " 
		<< lecturer << endl;
}

}
