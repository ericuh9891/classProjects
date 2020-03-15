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
	int pr_count = 0;
	char buf[line_size];

	if(argc != 2){
		printf("invalid number of arguments\n");
		exit(EXIT_FAILURE);
	}
	if(pr_limit = atoi(argv[1]) <= 0){
		printf("invalid argument for number of processes\n");
		exit(EXIT_FAILURE);
	}
//Setup for executing multiple processes
	FILE *input = fdopen(0,"r");
	pid_t pid;
	char *program_name;
	char *arg1;
	char *arg2;
	int status;
	while(fgets(buf, line_size, input) != NULL){
		pid = fork();
//Child execution
		if(pid == 0){
			program_name = strtok(buf," ");
			arg1 = strtok(NULL," ");
			arg2 = strtok(NULL," ");
			execl(program_name,arg1,arg2,"NULL");
			printf("executing program: %s ",buf);
			pr_count++;
		}
//Parent execution
		if(pid > 0){
			if(pr_limit != pr_count){
				waitpid(pid,&status,WNOHANG);
				pr_count--;
			}
			else{
				wait(&status);
				pr_count--;
			}
		}
//		printf("%s%c",buf,'\0');
	}
	exit(EXIT_SUCCESS);
	return 0;
}

