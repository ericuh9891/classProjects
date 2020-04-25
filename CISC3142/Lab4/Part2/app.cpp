#include <iostream>
#include "student.h"
#include <fstream>

using namespace std;

int main(int argc, char*argv[]){
/*
	Student student;
	student.set_name(string("Eric"));
	student.set_id(1001);
	cout << student.get_id() << endl;
	cout << student.get_name() << endl;
	Course calculus(1201,'A');
	cout << calculus.get_id() << endl;
	cout << calculus.get_grade() << endl;
	student.add_course(calculus);
	int result = student.get_course(calculus);
	cout << result << endl;
	Course intro_java(1115,'A');
	student.add_course(intro_java);
	result = student.get_course(intro_java);
	cout << result << endl;
	cout << student.total_courses() << endl;
	vector<Course>::iterator iter = student.access_all_courses().begin();
	vector<Course>::iterator end = student.access_all_courses().end();
	for(iter; iter != end; ++iter){
		cout << iter->get_id() << endl;
	}
*/
	vector<Student> students;
	int student_id;
	string student_name;

	int course_id;
	int course_credits;
	char course_grade;

	ifstream input("student.dat");
	while(!input.eof()){
		input >> student_id;
			if(student_id == -1)
				break;
		cout << student_id << endl;
		input >> student_name;
		cout << student_name << endl;
		students.push_back(Student(student_id,student_name));
		while(!input.eof()){
			input >> course_id;
			cout << course_id << endl;
				if(course_id == -1)
					break;
			input >> course_credits;
			cout << course_credits << endl;
			input >> course_grade;
			cout << course_grade << endl;
			students[students.size()-1].add_course(Course(course_id,course_credits,course_grade));
		}
	}
	return 0;
}
