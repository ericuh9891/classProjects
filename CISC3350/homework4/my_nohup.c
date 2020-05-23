/******************************
Eric Y. U Huang
CISC 3350 - TR3 Spring 2020
Professor Y. Xiang
Due date: 5/25/2020

This program simulates a simplified nohup command based on the description from
http://www.gnu.org/software/coreutils/manual/html_node/nohup-invocation.html#nohup-invocation
First it checks command arguments. Program exits if no command or another program is supplied.
If a command or program is supplied, STDIN is redirected to /dev/null. STDOUT AND STDERR is redirected 
to a file called nohup.out. If nohup.out doesn't exist then it is created in the current directory.
If any redirection fails then program exits. Signals SIGHUP and SIGQUIT are set to be ignored so
the supplied command or program will run without being linked to a terminal. If signals fail to
be set to ignore then program exits. Otherwise execl() is called to run the command or program.
******************************/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv){
/* Command line processing */
	if(argc <= 1){
		errno = EINVAL;
		perror("No command was supplied to my_nohup");
		exit(EXIT_FAILURE);
	}
/* Redirecting STDIN */
	int input;
	int dup_in_ret;
	if(isatty(STDIN_FILENO)){
		input = open("/dev/null", O_WRONLY);
		if(input == -1){
			perror("Could not open special device file null");
			exit(EXIT_FAILURE);
		}
		dup_in_ret = dup2(input,STDIN_FILENO);
		if(dup_in_ret == -1){
			perror("Unable to redirect STDIN to /dev/null");
			exit(EXIT_FAILURE);
		}
	}
/* Redirecting STDOUT */
	int output;
	int dup_out_ret;
	if(isatty(STDOUT_FILENO)){
		output = open("nohup.out",O_CREAT | O_WRONLY | O_APPEND);
		if(output == -1){
			perror("Could not open or create file 'nohup.out'");
			exit(EXIT_FAILURE);
		}
		dup_out_ret = dup2(output,STDOUT_FILENO);
		if(dup_out_ret == -1){
			perror("Unable to redirect STDOUT to 'nohup.out'");
			exit(EXIT_FAILURE);
		}
	}
/* Redirecting STDERR */
	int dup_error_ret;
	if(isatty(STDERR_FILENO)){
		dup_error_ret = dup2(output,STDERR_FILENO);
		if(dup_error_ret == -1){
			perror("Unable to redirect STDERR to 'nohup.out'");
			exit(EXIT_FAILURE);
		}
	}

/* Setting up process to ignore SIGHUP and SIGQUIT */
	struct sigaction sa_hup;
	sa_hup.sa_handler = SIG_IGN;
	if(sigaction(SIGHUP,&sa_hup,NULL)){
		perror("Unable to modify signal handler");
		exit(EXIT_FAILURE);
	}
	struct sigaction sa_quit;
	sa_quit.sa_handler = SIG_IGN;
	if(sigaction(SIGQUIT,&sa_quit,NULL)){
		perror("Unable to modify signal handler");
		exit(EXIT_FAILURE);
	}
/* Runs passed in program */
	int exec_status = execv(argv[1],argv+1);
	if(exec_status == -1){
		char command[100] = "/bin/";
		strcat(command,(argv[1]));
		exec_status = execv(command,argv+1);
		if(exec_status == -1){
			perror("Unable to exec program");
			exit(EXIT_FAILURE);
		}
	}
	return 0;
}
