#include <iostream> 
#include "sqlite3.h"
using namespace std;

static int callback(void *data, int argc, char **argv, char **azColName) {
	int i;
	if(data != NULL) {
		cout << (const char*)data << endl;	
	}
	for(i=0; i<argc; i++) {
		cout << azColName[i] << ", " << (argv[i] ? argv[i] : "NULL") << endl;
	}
	return 0;
}


int main() {
	sqlite3* db;
	char *zErrMsg = 0;
	int rc;
	char const *sql;
	const char* data = "Callback function called!";

	rc = sqlite3_open("sdb.sqlite", &db);
	if( rc ) {
		cout << "Can't open db: " << sqlite3_errmsg(db) << endl;
	} else {
		cout << "Opened db successfully" << endl;
	}

	// Create Student Table
	sql = 	"CREATE TABLE IF NOT EXISTS STUDENT("\
		"ID		INTEGER PRIMARY KEY,"\
		"FIRSTNAME	TEXT	NOT NULL,"\
		"SURNAME	TEXT	NOT NULL,"\
		"AGE		INT	NOT NULL,"\
		"ADDRESS	CHAR(50));";

	// Execute SQL Statement
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if(rc != SQLITE_OK ) {
		cerr << "SQL error: " << zErrMsg << endl;
	} else {
		cout << "Student Table Exists!" << endl;
	}

	// Insert Test Student
	sql =	"INSERT INTO STUDENT (ID, FIRSTNAME, SURNAME, AGE, ADDRESS)"\
		"VALUES(NULL, 'Dan', 'Roberts', 26, '337 Coutts Island Rd')";
	
	// Execute SQL Statement
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if(rc != SQLITE_OK) {
		cout << "Couldn't insert student: " << zErrMsg << endl;
	} else {
		cout << "Inserted student!" << endl;
	}

	// Select All Students
	sql = "SELECT * FROM STUDENT";

	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	if( rc != SQLITE_OK ) {
		cout << "Error getting students: " << zErrMsg << endl;
	} else {
		cout << "Retrieved Students!" << endl;
	}
	sqlite3_close(db);
	return 0;
}

