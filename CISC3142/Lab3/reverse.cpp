#include "reverse.h"
#include <string>
#include <iostream>

using namespace std;

template <typename T>
void play_with(T array[],int size){
	cout << "Before: ";
	print(array, size);
	cout << endl;
	reverse(array,size);
	cout << "After: ";
	print(array, size);
	cout << endl << endl;
}

int main(){
	
	int int_array[5] = {10,20,30,40,50};
	double double_array[6] = {10.5,20.5,30.5,40.5,50.5,60.5};
	string string_array[] = {"ABC","DE","FGHI","JK"};

	cout << "Playing with int" << endl;
	play_with(int_array,5);

	cout << "Playing with double" << endl;
	play_with(double_array,6);

	cout << "Playing with string" << endl;
	play_with(string_array,4);

	return 0;
}
