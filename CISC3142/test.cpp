#include <iostream>

using namespace std;

void add_one_toAll(int& v[]){
	for(auto i : v[]){
		i++;
	}
}

int main(){
	int v[] {0,1,2,3,4,5,6,7,8,9};
	add_one_toALL(v);
	return 0;
}

