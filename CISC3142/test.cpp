#include <iostream>

using namespace std;
class Counter{
	public:
		Counter(int x, int y);
		void decrement();
		void increment();
		int getValue();
		static int getNCounters();
	private:
		int counter;
		int limit;
		static int nCounters;
};
/*
Counter::Counter(int x, int y){
	counter = x;
	limit = y;
	Counter::nCounters++;
}
*/
int Counter::nCounters = 0;
void Counter::increment(){
	if(counter < limit)
		counter++;
}
int Counter::getNCounters(){
	return nCounters;
}
int main(){
	
	Counter obj(1,1);
	


































/*

void printInt(int* x){
	cout << "value of x: " << x << endl;
	*x = 13;
	cout << "value of x: " << x << endl;
}

int main(){
int a = 11;
char c = 'c';
int& b = a;

printInt(&c);

	cout << "value of a: " << a << endl;


void doubleIt(int* x){
	*x = *x * 2;
}

int main(){

int savings = 7;
int* savings_ptr = &savings;

cout << "savings = " << savings << endl;
doubleIt(savings_ptr);
cout << "after calling doubleIt, savings = " << savings << endl;


void minMax(int a, int b, int c, int& large, int& small){
	int nums[3] = {a,b,c};
	int temp = 0;
	for(int i = 0; i < 3; i++){
		if(temp < nums[i]) temp = nums[i];
	}
	large = temp;
	for(int i = 0; i < 3; i++){
		if(temp > nums[i]) temp = nums[i];
	}
	small = temp;
}

int main(){
	int a = 31;
	int b = 5;
	int c = 12;
	int large = 0;
	int small = 0;
	minMax(a,b,c,large,small);
	cout << "large is: " << large << endl;
	cout << "small is: " << small << endl;
*/
	return 0;
}

