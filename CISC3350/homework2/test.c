//function experiment program

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define pr_limit 2

int main(){
	int child_pids[pr_limit];
	printf("data at array [%d] = %d\n",1,child_pids[1]);
	if(child_pids[1] == 0)
		printf("Data is tested");








/*
	char *fgets_status;
//	fgets_status = "./testsim 2 7";
	if(fgets_status == NULL)
		printf("fgets_status is NULL\n");
//		printf("%s\n",fgets_status); 

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
*/
	return 0;
}
