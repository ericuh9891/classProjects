#include <vector>
#include <string>
#include <iostream>
#include "course.h"
#ifndef STUDENT_H
#define STUDENT_H

class Student{
	public:
		Student(int id, std::string name);
		int get_id();
		std::string get_name();
		std::vector<Course>& access_all_courses();
		void add_course(Course course);
		double get_GPA();
		void print(std::ostream &os);
	private:
		int id;
		std::string name;
		std::vector<Course> courses_taken;
		double GPA;
		void calc_GPA();
};

inline std::ostream &operator <<(std::ostream &os, Student &student){
	student.print(os);
	return os;
}
#endif
