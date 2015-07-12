#ifndef STUDENT_H
#define STUDENT_H
#include <string>
using namespace std;

namespace sdb {
	
class Student {
	private:
		int id;
		string firstName;
		string surname;
		string dob; // date of birth
		string address;
	public:
		Student();
		Student(int _id, string _firstName, string surname, string _dateOfBirth, string _address);
		int getId() { return id; }
		string getFirstName() { return firstName; }
		string getSurname() { return surname; }
		string getDateOfBirth() { return dob; }
		string getAddress() { return address; }
		void setFirstName(string _firstName) { firstName = _firstName; }
		void setSurname(string _surname) { surname = _surname; }
		void setDateOfBirth(string _dob) { dob = _dob; }
		void setAddress(string _address) { address = _address; } 
		void print();
};

}

#endif
