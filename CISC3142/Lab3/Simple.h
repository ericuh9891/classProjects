#include <string>
#include <iostream>

template <typename T>
class Simple{
	public:
		Simple(T val){
			this->val = val;
		}
		T getVal(){
			return val;
		}
		void setVal(T val){
			this->val = val;
		}
		void print(){
			std::cout << val;
		}
	private:
		T val;
};
