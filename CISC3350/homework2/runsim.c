#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

#define line_size 2621440

int main(int argc, char **argv){
//Argument checking
	int pr_limit;
	

	if(argc != 2){
		printf("invalid number of arguments\n");
		exit(EXIT_FAILURE);
	}
	if(atoi(argv[1]) <= 0 || atoi(argv[1]) >= 30000){
		printf("invalid argument for number of processes\n");
		exit(EXIT_FAILURE);
	}
//Version 2
//Setup for executing multiple processes
	char buf[line_size];
	pid_t pid;
	int execv_status;
	int pr_count;
	char *arg0;
	char *arg1;
	char *arg2;
	

	FILE *input = fdopen(0,"r");
		if(input == NULL)
			perror("Error get FILE stream from stdin");
	
	do{
		fgets(buf,line_size,input);
		if(buf != NULL && pr_limit != pr_count){
			pid = fork();
			pr_count++;
			if(pid == -1){
				perror("Fork failed");
			}
//Child Process
			if(pid == 0){
				arg0 = strtok(buf," ");
				arg1 = strtok(NULL," ");
				arg2 = strtok(NULL," ");
				char *argv_list[] = {arg0,arg1,arg2,NULL};
				printf("Starting child process: %jd, running %s\n",getpid(),buf);
				execv_status = execv(arg0,argv_list);
				if(execv_status == -1){
					perror("Exec failed");
				}
			}
		}
	}while(buf != NULL && pr_count != 0);

	return 0;
}

