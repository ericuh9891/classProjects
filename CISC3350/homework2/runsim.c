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
	if(atoi(argv[1]) <= 0 || atoi(argv[1]) > 30000){
		printf("invalid argument for number of processes\n");
		exit(EXIT_FAILURE);
	}
//Version 2
//Setup for executing multiple processes
	pr_limit = atoi(argv[1]);
	char buf[line_size];
	char *fgets_status = ""; 
	pid_t pid;
	int execv_status;
	int pr_count = 0;
	char *arg0;
	char *arg1;
	char *arg2;
	int child_pids[pr_limit];
	int status;
	int wait_return;
	

	FILE *input = fdopen(0,"r");
		if(input == NULL){
			perror("Error getting FILE *stream from stdin");
			exit(EXIT_FAILURE);
		}
	
	do{
		if(pr_limit != pr_count){
			fgets_status = fgets(buf,line_size,input);
		}
		if(fgets_status != NULL && pr_limit != pr_count){
			pid = fork();
			if(pid == -1){
				perror("Fork failed");
				exit(EXIT_FAILURE);
			}
			pr_count++;
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
					exit(EXIT_FAILURE);
				}
			}
//End of Child Process Code
//Continuation of Parent Process Code
/*
//Loops the int array and stores the child pid in an empty(0 value is considered empty) index
			for(int i = 0; i < pr_limit; i++){
				if(child_process[i] == 0){
					child_procecss[i] == pid;
					break;
				}
			}
*/
		}
		else{
			wait_return = waitpid(0,&status,WNOHANG);
			if(wait_return == -1){
				perror("Waitpid call returned error");
			}
			if(wait_return > 0){
				printf("child_pid = %d ", wait_return);
				pr_count--;
				if(WIFEXITED(status)){
					printf("Normal termination with exit status = %d\n", WEXITSTATUS(status));
				}
				if(WIFSIGNALED(status)){
					printf("Killed by signal = %d\n", WTERMSIG(status));
				}
			}
		}
	}while(buf != NULL && pr_count != 0);
	return 0;
}

