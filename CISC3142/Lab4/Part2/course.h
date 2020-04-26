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
	private:
		int id;
		int credits;
		char grade;
};
