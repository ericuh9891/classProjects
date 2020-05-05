#include <iostream>
#include "student.h"
#ifndef STUDENT_CPP
#define STUDENT_CPP

Student::Student(int id, std::string name){
	this->id = id;
	this->name = name;
}
int Student::get_id(){
	return id;
}
std::string Student::get_name(){
	return name;
}
std::vector<Course>& Student::access_all_courses(){
	return courses_taken;
}
void Student::add_course(Course course){
	courses_taken.push_back(course);
}
void Student::calc_GPA(){
	double points_earned = 0;
	double credits_attempted = 0;
	for(int i = 0; i < courses_taken.size(); ++i){
		switch(courses_taken[i].get_grade()){
			case 'A':
				points_earned += 4*courses_taken[i].get_credits();
				break;
			case 'B':
				points_earned += 3*courses_taken[i].get_credits();
				break;
			case 'C':
				points_earned += 2*courses_taken[i].get_credits();
				break;
			case 'D':
				points_earned += 1*courses_taken[i].get_credits();
				break;
			case 'F':
				points_earned += 0;
				break;
		}
		credits_attempted += courses_taken[i].get_credits();
	}
	GPA = points_earned/credits_attempted;
}
double Student::get_GPA(){
	calc_GPA();
	return GPA;
}
void Student::print(std::ostream &os){
	os << id << " " << name << ": " << get_GPA() << std::endl;
	for(auto i : courses_taken){
		os << "   " << i << std::endl;
	}
}

#endif
