#include "cstring.cpp"
#include <cstdio>

//using namespace mystring;

int main(){
	char str1[] = "Hello";
	char str2[] = "Boring";
	printf("str1 = %s\n", str1);
	printf("str2 = %s\n", str2);
	strcpy(str2,str1);
	printf("str1 = %s\n", str1);
	printf("str2 = %s\n", str2);
	return 0;
}
