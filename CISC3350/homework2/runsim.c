/**********************************
Eric Y. U Huang
CISC 3350 - TR3 Spring 2020
Professor Y. Xiang
Due Date: 3/24

Program creates multiple processes to run another program, testsim,
based on supplied command line arguments. First, the command line 
arguments are checked to ensure proper number of processes to
run is correct. If supplied number is less than 1 or greater than
30,000 then proper messages are printed to stdout and program 
terminates. If proper command line arguments are supplied, program
proceeds to declare and initialize varies variables for creating
multiple processes. A FILE *stream to stdin is created for reading in
user input or piped in file. Program enters a do while loop which
contains the main logic. If a line is availible then it is read in
and fork plus execv is called to create a child process to run
the testsim program. Loop continues to iterate as long as there are
lines to be read in or number of running child processes has not 
reached zero. Please see comments in source code to see more 
detailed explainations.

**********************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#define line_size 2621440

int main(int argc, char **argv){
/*Command line argument checking*/
	if(argc != 2){
		printf("invalid number of arguments\n");
		exit(EXIT_FAILURE);
	}
	if(atoi(argv[1]) <= 0 || atoi(argv[1]) > 30000){
		printf("invalid argument for number of processes\n");
		exit(EXIT_FAILURE);
	}
/*Setup of variables for executing multiple processes*/
	int pr_limit = atoi(argv[1]);
	char buf[line_size];
	char *fgets_status = "";
	pid_t pid;
	int execv_status;
	int pr_count = 0;
	char *arg0;
	char *arg1;
	char *arg2;
	int status;
	int wait_return;
/*Creates a FILE steam pointer for reading from stdin*/
	FILE *input = fdopen(0,"r");
		if(input == NULL){
			perror("Error getting FILE *stream from stdin");
			exit(EXIT_FAILURE);
		}
/*
Loop contains the main logic of reading in a line from stdin, then
calling fork() and execv to run the testsim program. The variables
pr_limit controls the max number of processes to be run concurrently
and pr_count keeps track of the number of running processes.
Each line read in will be executed by calling fork(). The resulting
child process breaks up the read in line into tokens and stores them
in a string array pointers which is supplied to execv. Meanwhile the
parent process will call waitpid() for any of it's child processes.
*/
	do{
/*
fgets() is guaranteed to execute on first iteration of loop since
pr_limit cannot be initialized to anything lower than 1 and pr_count
is initialized to 0 before entry to the loop
*/
		if(pr_limit != pr_count){
			fgets_status = fgets(buf,line_size,input);
		}
/*
If a line is read in and the number of current running child processes
has not exceeded the limit, then fork is called and the child procecss
counter, pr_count, is incremented. Paired else statement calls waitpid()
if there are no more lines availible or number of child processes has
reach the child process limit.
*/
		if(fgets_status != NULL && pr_limit != pr_count){
			pid = fork();
			if(pid == -1){
				perror("Fork failed");
				exit(EXIT_FAILURE);
			}
			pr_count++;
/*
CHILD PROCESS CODE
The read in line is broken into string tokens that are provided to
execv as an string array pointers. If execv fails, then child will self
terminate with exit() call with EXIT_FAILURE.
*/
			if(pid == 0){
				arg0 = strtok(buf," ");
				arg1 = strtok(NULL," ");
				arg2 = strtok(NULL," ");
				char *argv_list[] = {arg0,arg1,arg2,NULL};
				printf("Starting child process : %jd, running %s %s %s",getpid(),arg0,arg1,arg2);
				execv_status = execv(arg0,argv_list);
				if(execv_status == -1){
					perror("Execv failed");
					exit(EXIT_FAILURE);
				}
			}
/*End of Child Process Code*/
/*Continuation of Parent Process Code*/
		}
/*
If no more lines are availible or child processes has reached
the process limit set by pr_limit then waitpid() is called to
wait on any child process. If a child process is waited on, then
information pertaining to it's status is printed to stdout.
*/
		else{
			wait_return = waitpid(0,&status,WNOHANG);
/*
If waitpid() returns an error, errno is checked to see if
waitpid was called while there are no more which can occur
when pr_limit is set to 1
*/
			if(wait_return == -1){
				if(errno == ECHILD){
					printf("No more child processes left\n");
				}
				else{
					perror("Waitpid call returned error");
				}
			}
/*
On a successful waitpid() call, information pertaining to
the waited on child process is printed to stdout and 
pr_count is decremented
*/
			if(wait_return > 0){
				pr_count--;
				printf("child_pid = %d : ", wait_return);
				if(WIFEXITED(status)){
					if(WEXITSTATUS(status) == EXIT_FAILURE){
						printf("Self Termination from failed execv call with exit status = %d\n", WEXITSTATUS(status));
					}
					else{
						printf("Normal termination with exit status = %d\n", WEXITSTATUS(status));
					}
				}
				if(WIFSIGNALED(status)){
					printf("Killed by signal = %d\n", WTERMSIG(status));
				}
				if(WIFSTOPPED (status)){
					printf("Stopped by signal = %d\n", WSTOPSIG(status));
				}
				if(WIFCONTINUED(status)){
					printf("Continued\n");
				}
			}
		}
/*
Loop terminates when there are no more lines availible or the number 
of running processes reaches zero
*/
	}while(fgets_status != NULL || pr_count != 0);
	return 0;
}
