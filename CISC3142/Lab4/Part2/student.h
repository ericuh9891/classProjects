#include <iostream>
#include "course.h"
#include <vector>

using namespace std;

class Student{
	public:
		Student(int id, string name){
			this->id = id;
			this->name = name;
		}
		int get_id(){
			return id;
		}
		string get_name(){
			return name;
		}
		void set_id(int id){
			this->id = id;
		}
		void set_name(string name){
			this->name = name;
		}
		void add_course(Course course){
			courses_taken.push_back(course);
		}
		int get_course(Course course){
			for(int i = 0; i < courses_taken.size(); i++){
				if(courses_taken[i].get_id() == course.get_id()){
					return i;
				}
			}
			return -1;
		}
		Course get_course(int position)const{
			return courses_taken[position];
		}
		int total_courses(){
			return courses_taken.size();
		}
		vector<Course>& access_all_courses(){
			return courses_taken;
		}
	private:
		int id;
		string name;
		vector<Course> courses_taken;
		int course_size;
};
