#include <iostream>
#include <string>

template <typename T>
void reverse(T array[], int size){
	T temp;
	int i = 0;
	int j = size - 1;

	while(i < j){
		temp = array[i];
		array[i] = array[j];
		array[j] = temp;
		i++;
		j--;
	}
}
template<typename T>
void print(T array[], int size){
	std::cout << "{";
	for(int i = 0; i < size; i++){
		std::cout << array[i];
		if(i != size - 1)
			std::cout << ", ";
	}
	std::cout << "}";
}
