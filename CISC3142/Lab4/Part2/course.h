class Course{
	public:
		Course(int id,int credits, char grade){
			course_id = id;
			course_credits = credits;
			course_grade = grade;
		}
		int get_id(){
			return course_id;
		}
		int get_course_credits(){
			return course_credits;
		}
		char get_grade(){
			return course_grade;
		}
		void set_id(int  id){
			this->course_id = id;
		}
		void set_grade(char grade){
			this->course_grade = grade;
		}
	private:
		int course_id;
		int course_credits;
		char course_grade;
};
