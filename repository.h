#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <iostream>
#include <vector>
#include "student.h"
#include "sqlite3.h"

namespace sdb {

class Repository {
	private:
		sqlite3* db;
	public:
		~Repository();
		bool init();
		bool getStudents(vector<Student> &sv);
		bool insertStudent(Student s);
};

}

#endif
