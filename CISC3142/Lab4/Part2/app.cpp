#include <iostream>
#include <fstream>
#include <algorithm>
#include "student.cpp"

using namespace std;

bool compare(Student &s1, Student &s2);

int main(int argc, char*argv[]){

	vector<Student> students;

	int student_id;
	string student_name;

	int course_id;
	int course_credits;
	char course_grade;

	ifstream input("students.data");
		if(input.fail()){
			cerr << "Could not open file" << endl;
			return -1;
		}
	input >> student_id;
	while(!input.eof()){
		input >> student_name;
		students.push_back(Student(student_id, student_name));
		input >> course_id;
		while(!input.eof() && course_id != -1){
			input >> course_credits;
			input >> course_grade;
			students[students.size()-1].add_course(Course(course_id,course_credits,course_grade));
			input >> course_id;
		}
		input >> student_id;
	}
	input.close();

	sort(students.begin(),students.end(),compare);

	for(auto i:students)
		cout << i;

	cout << endl << students.size() << " records processed" << endl;
	return 0;
}

bool compare(Student &s1, Student &s2){
	return s1.get_GPA() > s2.get_GPA();
}

