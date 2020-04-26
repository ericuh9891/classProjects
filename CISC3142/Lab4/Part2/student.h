#include "course.h"
#include <vector>
#include <string>

using namespace std;

class Student{
	public:
		Student(int id, string name);
		int get_id();
		string get_name();
		vector<Course>& access_all_courses();
		void add_course(Course course);
		double get_GPA();
	private:
		int id;
		string name;
		vector<Course> courses_taken;
		double GPA;
		void calc_GPA();
};
