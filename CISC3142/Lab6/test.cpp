#include "cstring.cpp"
#include <cstdio>

//using namespace mystring;

int main(){
//strrchr test

	char *str1 = "Hello";
	char c = 'd';
	str1 = strrchr(str1,c);
	if(str1 == nullptr)
		printf("nullptr");
	else	
		printf("%s\n",str1);

//strchr test
/*
	char *str1 = "Hello";
	char c = 'e';
	str1 = strchr(str1,c);
	if(str1 == nullptr)
		printf("nullptr");
	else
		printf("%s\n",str1);
*/
//strcmp test
/*
	char str1[] = "Hella";
	char str2[] = "Helld";
	printf("%d\n",strcmp(str1,str2));
*/	
//strlen testing
/*
	char str1[] = "Hello";
	char str2[] = "Boring";
	char str3[] = "Goodbye";
	printf("length of str1: %d\n", strlen(str1));
	printf("length of str1: %d\n", strlen(str2));
	printf("length of str1: %d\n", strlen(str3));
*/

//strcat testing
/*
	char str1[] = "Hello";
	char str2[] = "GoodByeGoodByeGoodByeGoodByeGoodByeGoodByeGoodByeGoodByeGoodByeGoodByeGoodByeGoodByeGoodBye";
	char str3[100];
	printf("str3 = %s\n",str3);
	strcat(str3,str1);
	printf("str3 = %s\n",str3);
	strcat(str3,str2);
	printf("str3 = %s\n",str3);
	strcat(str3,str2);
	printf("str3 = %s\n",str3);
	strcat(str3,str2);
	printf("str3 = %s\n",str3);
	strcat(str3,str2);
	printf("str3 = %s\n",str3);
*/
//strcpy testing
/*
	char str1[] = "Hello";
	char str2[] = "Boring";
	char str3[] = "Goodbye";
	printf("str1 = %s\n", str1);
	printf("str3 = %s\n", str3);
	strcpy(str1,str3);
	printf("str1 = %s\n", str1);
	printf("str3 = %s\n", str3);
	return 0;
*/
}
