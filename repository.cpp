#include <iostream>
#include <cstring>
#include <cstdlib>
#include "student.h"
#include "repository.h"
#include "sqlite3.h"

namespace sdb {

char const * DB_FILE = "sdb.sqlite";

// Could pass through the array of students, then build up into local globals
// all the data, then create a student and pass it in. 
// Could build it up inside a student object with one global

static int callback(void *data, int argc, char **argv, char **azColName) {
        int i;
        if(data != NULL && argc == 5) {
		Student s(atoi(argv[0]), argv[1], argv[2], argv[3], argv[4]);
		((vector<Student>*)data)-> push_back(s);
	}
        return 0;
}

bool Repository::getStudents(vector<Student> &sv) {
	const char* data = "Callback function called!";
	char *zErrMsg = 0;

	// Select All Students
        char const * sql = "SELECT * FROM STUDENT";

        int rc = sqlite3_exec(db, sql, callback, (void*)&sv, &zErrMsg);
        if( rc != SQLITE_OK ) {
		return false;
        }
	return true;
}

bool Repository::insertStudent(Student s) {

	char *zErrMsg = 0;
	 // Insert Test Student
	char* sql = sqlite3_mprintf(
		"INSERT INTO STUDENT (ID, FIRSTNAME, SURNAME, DOB, ADDRESS)"
		"VALUES(NULL, '%q', '%q', '%q', '%q')",
		s.getFirstName().c_str(),
		s.getSurname().c_str(),
		s.getDateOfBirth().c_str(),
		s.getAddress().c_str()
	);

        // Execute SQL Statement
        int rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
        if(rc != SQLITE_OK) {
		return false;
        }
	return true;
}

bool Repository::init() {
       	char *zErrMsg = 0;
       	int rc;
       	char const *sql;
       	const char* data = "Callback function called!";

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
        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
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


