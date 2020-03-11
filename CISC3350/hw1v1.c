/******************************
TODO list
-Create a method parsefile() to keep parsing the lines from a file and compare them to see if they're the same
-parsefile() needs to print to a file if ditated by command line args, if no output file is given in command line
	everthing needs to be printed to console/stdout. If no input file is given, then input needs to be take from console input/stdin
-A method or code to interpret command line args
-Comment Code
-Write summary in plain english of algorithm of code
-if there are additional options for command line args note it in summary
******************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h> //For stdin and stdout for C, scanf(), printf(), etc.
#include <string.h> //For using strings comparison methods in C
#include <errno.h> //Defines errno that the system calls will use and the use of function strerror() for printing error messages
#include <stdlib.h> //For using exit() when something fails in the program
#include <unistd.h> //For using close() to close files
#include <stdbool.h> //For using Boolean data type

int parseline(int input_fd,char *buf);
void clearbuf(char *buf);
void printstr(char *buf);
bool samelines(char *buf1,char *buf2, bool case_insensitive);
void parsefile(char *infile, char *outfile, bool case_insensitive);

int main(int argc, char *argv[]){
	//***** Parsing the command line arguments *****//
	if(argc > 2){
		printf("Too many command line arguments \n");
		exit(-1);
	}
	//***** Parsing the command line arguments *****//

	//***** Variables *****//
	int input_fd; //Stores the file descriptor when opening the input file
	int output_fd; //Stores the file descriptor of the output file
	int close_infile; //Stores the return status of close() for input file
	int close_outfile; //Stores the return status of close() for output file
	char buf1[2048]; //char array to store the a line from read() for comparison
	char buf2[2048]; //char array to store the a line from read() for comparison
	errno = 0;
	int temp_errno = 0;
	int current_pos = 0;
	char test[10] = "Hello";

	parsefile("testfile","results",true);


//	printf("%i\n",parseline(input_fd,buf1));
//	printstr(buf1);
//	printf("%i\n",parseline(input_fd,buf2));
//	printstr(buf2);
//	if(samelines(buf1,buf2,true))
//		printf("Lines are the same\n");
//	else 
//		printf("Lines are not the same\n");
//	clearbuf(buf1);
//	printf("%i\n",parseline(input_fd,buf1));
//	printstr(buf1);
	return 0;
}
//***** Tested (Passed) *****//
int parseline(int input_fd,char *buf){
	printf("Entered parseline function\n");
	char c;
	int buf_pos = 0;
	int read_status = 1;
	while(read_status > 0){
		read_status = read(input_fd,&c,1);
		if(c == '\n'){
			buf[buf_pos] = '\0';
			break;
		}
//read() returning 0 means file pointer has reached end of file (EOF)
		if(read_status < 1){
			return 0;
		}
		buf[buf_pos] = c;
		buf_pos++;
	}
	return buf_pos;
}
//***** Tested (Passed) *****//
void clearbuf(char *buf){
	for(int i = 0; i <strlen(buf); i++){
		buf[i] = 0;
	}
}
//***** Tested (Passed) *****//
void printstr(char *buf){
	int len = strlen(buf);
	int start = 0;
	while(start < len){
		printf("%c",buf[start]);
		start++;
	}
	printf("\n");
}
//***** Tested (Passed) *****//
bool samelines(char *buf1, char *buf2, bool case_insensitive){
	int samelines;
	if(case_insensitive){
		samelines = strcasecmp(buf1,buf2);
		if(samelines == 0)
			return true;
	}
	else{
		samelines = strcmp(buf1,buf2);
		if(samelines == 0)
			return true;
	}
	return false;
}

int writeline(int fd, char *buf){
	int write_state = 0;
	write_state = write(fd,buf,strlen(buf));
	write(fd,"\n",1);
	if(write_state == -1){
		printf("Writing to file encountered an error: %s\n", strerror(errno));
		exit(-1);
	}
	return write_state;
}

void parsefile(char *infile, char *outfile, bool case_insensitive){
	printf("Entered parsefile function\n");
		//***** Open file input/read *****//
	int in_fd;
	int out_fd;
	int close_infile;
	int close_outfile;
	int temp_errno;
	int end_of_file = 1;
	char buf1[2048];
	char buf2[2048];
	char lastwrite[2048];
	char empty[2048];
	int cmp_result;
	int write_state;

	in_fd = open(infile,O_RDONLY);
	if(in_fd == -1){
		temp_errno = errno;
		printf("Unable to open input file \n");
		printf("Error: %s\n", strerror(errno));
		exit(-1);
	}
	printf("Input file opened\n");
		//***** Open file output/write *****//
	out_fd = open(outfile,O_WRONLY | O_APPEND);
	if(out_fd == -1){
		temp_errno = errno;
		printf("Unable to open output file \n");
		printf("Error: %s\n", strerror(errno));
		exit(-1);
	}
	printf("Output file opened\n");
	end_of_file = parseline(in_fd,buf1);
	if(end_of_file != 0){
		write(out_fd,buf1,strlen(buf1));
		write(out_fd,"\n",1);
		strcpy(lastwrite,buf1);
		printstr(buf1);
		strcpy(buf1,empty);
		end_of_file = parseline(in_fd,buf1);
	}
	while(end_of_file != 0){
		end_of_file = parseline(in_fd,buf2);
		if(samelines(buf1,buf2,case_insensitive)){
			if(!samelines(lastwrite,buf1,case_insensitive)){
				printf("Btyes written: %i\n",write(out_fd,buf1,strlen(buf1)));
				printf("Btyes written: %i\n",write(out_fd,"\n",1));
				strcpy(lastwrite,buf1);
				//clearbuf(buf1);
				//memset(buf1,0,strlen(buf1));
				strcpy(buf1,buf2);
				//clearbuf(buf2);
			}
		}
		else{
			if(!samelines(lastwrite,buf1,case_insensitive)){
				printf("Btyes written: %i\n",write(out_fd,buf1,strlen(buf1)));
				printf("Btyes written: %i\n",write(out_fd,"\n",1));
				printf("Btyes written: %i\n",write(out_fd,buf2,strlen(buf2)));
				printf("Btyes written: %i\n",write(out_fd,"\n",1));
				strcpy(lastwrite,buf2);
				//clearbuf(buf1);
				//memset(buf1,0,strlen(buf1));
				strcpy(buf1,buf2);
				//clearbuf(buf2);
			}
			else{
				write(out_fd,buf2,strlen(buf2));
				write(out_fd,"\n",1);
				strcpy(lastwrite,buf2);
				strcpy(buf1,buf2);
			}
		}
		strcpy(buf2,empty);
		//clearbuf(buf2);
		//end_of_file = parseline(in_fd,buf2);
		//printstr(buf2);
	}

		//***** Closes file after done reading *****//
	close_infile = close(in_fd);
	if(close_infile == -1){
		temp_errno = errno;
		printf("Closing file failed \n");
		printf("Error: %s\n", strerror(errno));
		exit(-1);
	}
	printf("Input file closed\n");
		//***** Closes file after done writing *****//
	close_outfile = close(out_fd);
	if(close_outfile == -1){
		temp_errno = errno;
		printf("Closing file failed \n");
		printf("Error: %s\n", strerror(errno));
		exit(-1);
	}
	printf("Output file closed\n");
	printf("exiting parsefile function\n");
}
