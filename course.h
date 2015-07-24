#ifndef COURSE_H 
#define COURSE_H
#include <string>
using namespace std;

namespace sdb {

class Course {
        private:
                int id;
                string name;
                string period;
                string description;
                string lecturer;
        public:
                Course();
                Course(int _id, string _name, string period, string _description, string _lecturer);

                int getId() { return id; }
                string getName() { return name; }
                string getPeriod() { return period; }
                string getDescription() { return description; }
                string getLecturer() { return lecturer; }

		void setName(string _name) { name = _name; }
                void setPeriod(string _period) { period = _period; }
                void setDescription(string _desc) { description = _desc; }
                void setLecturer(string _lecturer) { lecturer = _lecturer; }

                void print();
};

}

#endif

