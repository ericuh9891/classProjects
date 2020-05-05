#include <iostream>
#ifndef COURSE_H
#define COURSE_H

class Course{
	public:
		Course(int id,int credits, char grade){
			this->id = id;
			this->credits = credits;
			this->grade = grade;
		}
		int get_id(){
			return id;
		}
		int get_credits(){
			return credits;
		}
		char get_grade(){
			return grade;
		}
		void print(std::ostream &os)const{
			os << id << " (" << credits << " credits): " << grade;
		}
	private:
		int id;
		int credits;
		char grade;
};

inline std::ostream &operator <<(std::ostream &os, const Course &course){
	course.print(os);
	return os;
}

#endif
