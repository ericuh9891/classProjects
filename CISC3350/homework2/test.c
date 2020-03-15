//function experiment program

#include <string.h>
#include <stdio.h>

int main(){
	char str[80] = "./testsim 1 7";
	const char s[2] = " ";
	char *token;
	char *program_name;
	char *arg1;
	char *arg2;

	program_name = strtok(str," ");
	arg1 = strtok(NULL," ");
	arg2 = strtok(NULL," ");
	printf("%s\n",program_name);
	printf("%s\n",arg1);
	printf("%s\n",arg2);
/*
	token = strtok(str,s);

	while (token != NULL){
		printf(" %s\n", token);
		token = strtok(NULL,s);
	}
*/
	return 0;
}
