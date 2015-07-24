#include <iostream>
#include <cstring>
#include <cstdlib>
#include "student.h"
#include "repository.h"
#include "sqlite3.h"

namespace sdb {

char const * DB_FILE = "sdb.sqlite";

static int studentCallback(void *data, int argc, char **argv, char **azColName) {
        if(data != NULL && argc == 5) {
		Student s(atoi(argv[0]), argv[1], argv[2], argv[3], argv[4]);
		((vector<Student>*)data)-> push_back(s);
	}
        return 0;
}

static int courseCallback(void *data, int argc, char **argv, char **azColName) {
	if(data != NULL && argc == 5) {
		Course c(atoi(argv[0]), argv[1], argv[2], argv[3], argv[4]);
		((vector<Course>*)data)-> push_back(c);	
	}
	return 0;
}

static int existsCallback(void *data, int argc, char **argv, char **azColName) {
	if(data != NULL) {
		*((bool*)data) = true;
	}
	return 0;
}

bool Repository::getStudents(vector<Student> &sv, int studentId) {
        char const * sql;
	if(studentId == -1) {	
		// Select All Students
		sql = "SELECT * FROM STUDENT";
	} else {
		sql = sqlite3_mprintf(
			"SELECT * FROM STUDENT WHERE ID='%i'",
			studentId
		);
	}

        int rc = sqlite3_exec(db, sql, studentCallback, (void*)&sv, 0);
        if( rc != SQLITE_OK ) {
		return false;
        }
	return true;
}

bool Repository::insertStudent(Student s) {
	char* sql = sqlite3_mprintf(
		"INSERT INTO STUDENT (ID, FIRSTNAME, SURNAME, DOB, ADDRESS)"
		"VALUES(NULL, '%q', '%q', '%q', '%q')",
		s.getFirstName().c_str(),
		s.getSurname().c_str(),
		s.getDateOfBirth().c_str(),
		s.getAddress().c_str()
	);

        // Execute SQL Statement
        int rc = sqlite3_exec(db, sql, 0, 0, 0);
        if(rc != SQLITE_OK) {
		return false;
        }
	return true;
}

bool Repository::getCourses(vector<Course> &cv, int courseId) {
        char const * sql;
	if(courseId == -1) {	
		// Select All Courses
		sql = "SELECT * FROM COURSE";
	} else {
		sql = sqlite3_mprintf(
			"SELECT * FROM COURSE WHERE ID='%i'",
			courseId
		);
	}

        int rc = sqlite3_exec(db, sql, courseCallback, (void*)&cv, 0);
        if( rc != SQLITE_OK ) {
		return false;
        }
	return true;
}

bool Repository::insertCourse(Course c) {
	char* sql = sqlite3_mprintf(
		"INSERT INTO COURSE (ID, NAME, DESCRIPTION, PERIOD, LECTURER)"
		"VALUES(NULL, '%q', '%q', '%q', '%q')",
		c.getName().c_str(),
		c.getDescription().c_str(),
		c.getPeriod().c_str(),
		c.getLecturer().c_str()
	);

        // Execute SQL Statement
        int rc = sqlite3_exec(db, sql, 0, 0, 0);
        if(rc != SQLITE_OK) {
		return false;
        }
	return true;
}

bool Repository::studentExists(int studentId) {
	char* sql = sqlite3_mprintf(
                        "SELECT * FROM STUDENT WHERE ID='%i' LIMIT 1",
                        studentId
        );

	bool* exists = new bool;
	*exists = false;	
	int rc = sqlite3_exec(db, sql, existsCallback, (void*)exists, 0);  
	if(!*exists) {
		cout << "Student with id: '" << studentId << "' doesn't exist" << endl;
		return false;
	}
	if(rc != SQLITE_OK) {
		return false;
	}
	return true;	
}

bool Repository::courseExists(int courseId) {
	char* sql = sqlite3_mprintf(
                        "SELECT * FROM COURSE WHERE ID='%i' LIMIT 1",
                        courseId
        );

	bool* exists = new bool;
	*exists = false;	
	int rc = sqlite3_exec(db, sql, existsCallback, (void*)exists, 0);  
	if(!*exists) {
		cout << "Course with id: '" << courseId << "' doesn't exist" << endl;
		return false;
	}
	if(rc != SQLITE_OK) {
		return false;
	}
	return true;	
}

bool Repository::enrolStudent(int studentId, int courseId) {
	if(!studentExists(studentId)) {
		return false;
	}
	if(!courseExists(courseId)) {
		return false;
	}
	
	char* sql = sqlite3_mprintf(
		"INSERT INTO ENROLMENT (STUDENTID, COURSEID)"
		"VALUES('%i', '%i')",
		studentId,
		courseId
	);

        // Execute SQL Statement
        int rc = sqlite3_exec(db, sql, 0, 0, 0);
        if(rc != SQLITE_OK) {
		return false;
        }
	return true;
}


bool Repository::init() {
       	char *zErrMsg = 0;
       	int rc;
       	char const *sql;

       	rc = sqlite3_open(DB_FILE, &db);
       	if( rc ) {
               	cout << "Can't open db: " << sqlite3_errmsg(db) << endl;
		return false;
       	}

	// Define student table schema
        sql =   "CREATE TABLE IF NOT EXISTS STUDENT("\
                "ID             INTEGER PRIMARY KEY,"\
                "FIRSTNAME      TEXT    NOT NULL,"\
                "SURNAME        TEXT    NOT NULL,"\
                "DOB            TEXT    NOT NULL,"\
                "ADDRESS        CHAR(50));";

        // Create student table
        rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
        if(rc != SQLITE_OK ) {
                cerr << "SQL error: " << zErrMsg << endl;
		return false;
        }

	// Define course table schema
	
	sql = 	"CREATE TABLE IF NOT EXISTS COURSE(" 
		"ID		INTEGER PRIMARY KEY," 
		"NAME		TEXT NOT NULL," 
		"DESCRIPTION	TEXT NOT NULL," 
		"PERIOD		TEXT NOT NULL," 
		"LECTURER	TEXT NOT NULL);"; 

	// Create course table 
	rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg); 
	if(rc != SQLITE_OK ) { 
		cerr << "SQL error: " << zErrMsg << endl; 
		return false; 
	} 

	// Define enrolment table schema
	sql = 	"CREATE TABLE IF NOT EXISTS ENROLMENT(" 
		"STUDENTID	INTEGER NOT NULL,"
		"COURSEID	INTEGER NOT NULL,"
		"UNIQUE(STUDENTID, COURSEID));";
	
	// Create course table
        rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
        if(rc != SQLITE_OK ) {
                cerr << "SQL error: " << zErrMsg << endl;
		return false;
        }

	return true;
}

Repository::~Repository() { 
	sqlite3_close(db);
}

}


