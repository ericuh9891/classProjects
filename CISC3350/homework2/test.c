//function experiment program

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	char str[13] = "./testsim 3 2";

//	FILE *input = fdopen(0,"r");
//	fgets(str,300000,input);
	char *arg0 = strtok(str," ");
	char *arg1 = strtok(NULL," ");
	char *arg2 = strtok(NULL," ");
	char *argv_list[] = {arg0,arg1,arg2,NULL};
	if(execv(arg0,argv_list) == -1)
		perror("execv failed");

//	int arg2_int = atoi(arg2);
//	printf("%s %s %s\n",arg0,arg1,arg2);
//	printf("size of arg2 = %d\n",sizeof arg2_int);

//	execl(arg0,arg1,arg2,(char *)0);
	
	return 0;
}
