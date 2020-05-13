#include <iostream>
#include "rational.h"
#include "rational_exception.h"

using namespace std;

int main(){
	Rational r1(1,2);
	Rational r2(2,4);
	cout << (r1+r2) << endl;
	return 0;
}
