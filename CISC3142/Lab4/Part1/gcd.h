#include <stdlib.h>
int gcd(int num1, int num2){
	num1 = abs(num1);
	num2 = abs(num2);
	if(num2 == 0)
		return num1;
	else
		return gcd(num2, num1%num2);
}
