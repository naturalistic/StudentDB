#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <iostream>
#include <vector>
#include "course.h"
#include "student.h"
#include "sqlite3.h"

namespace sdb {

class Repository {
	private:
		sqlite3* db;
		bool studentExists(int studentId);
		bool courseExists(int courseId);
	public:
		~Repository();
		bool init();
		bool getStudents(vector<Student> &sv, int studentId = -1);
		bool getCourses(vector<Course> &cv, int courseId = -1);
		bool insertStudent(Student s);
		bool insertCourse(Course c);
		bool enrolStudent(int studentId, int courseId);
};

}

#endif
