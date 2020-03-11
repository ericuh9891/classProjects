/******************************
Eric Y. U Huang
CISC 3350 - TR3 Spring 2020
Professor Y. Xiang
Due date: 2/20/2020

Program functions similar to the uniq command in linux command line.
There is an option of -i similar to uniq to turn on case insensitivity.
Explanation of the algorithms for parsing the different command line arguments
as well as the the algorithms for opening, reading, writing, and closing files
are included as comments preceding the source code of the related functions.
Helper and wrapper functions for read and write have comments explaining the
functions are placed preceding the code. Structure of the source code is
the function headers, main(), then the various helper and wrapper functions
at the bottom. 

******************************/

#include <sys/types.h>//For open()
#include <sys/stat.h>//For open()
#include <fcntl.h>//For open()
#include <stdio.h> //For stdin and stdout for C, scanf(), printf(), etc.
#include <string.h> //For using strings comparison methods in C
#include <errno.h> //Defines errno that the system calls will use and the use of function strerror() for printing error messages
#include <stdlib.h> //For using exit() when something fails in the program
#include <unistd.h> //For using close() to close files
#include <stdbool.h> //For using Boolean data type

//Function headers
int parseline(int input_fd,char *buf);
void clearbuf(char *buf);
void printstr(char *buf);
bool samelines(char *buf1,char *buf2, bool case_insensitive);
void parsefile(char *infile, char *outfile, bool case_insensitive);
int writeline(int fd, char *buf);
void parsestdio(int in_fd, int out_fd, bool case_insensitive);
void parsefilestdout(char *infile, int out_fd, bool case_insensitive);

int main(int argc, char *argv[]){
	//***** Checks for valid number of command line arguments *****//
	if(argc > 4){
		printf("Too many command line arguments \n");
		exit(-1);
	}
	//***** Variables *****//
	int input_fd; //Stores the file descriptor when opening the input file
	int output_fd; //Stores the file descriptor of the output file
	bool case_insensitive = false;
	//***** Parsing the command line arguments *****//
/*
*Multiple nested switch statements to handle different command line args
*Support commands are:
Zero Argument: With no arguments, program behaves similar to uniq commmand and prints
	all user input onto console. Program can be used with input and/or output redirection
	to specify input and/or output files.
*One Argument: -i option to turn on case insensitive filtering or input file path.
	if -i is the argument then program will behave similar to uniq command and
	print all user input into console. if -i is used with input and/or output 
	redirection then program will use the input redirection as the input file 
	and if given an output redirection, then all filtered outputs will be
	written into output file. If a file path is given as argument then file 
	contents will be filtered without case insensitivity and printed to console
	output redirection can be used to print to a file.
Two Argument: -i option to turn on case insenstive and input file path or input
	file path and output file path. if -i is the first argument then the program 
	will take the second argument as input file path and filter
	the input file's content with case insensitivity and print to console.
	If first argument is an input file path then the program will take the contents 
	of input file and print to the file path of the second argument without
	case insensitivity. Output redirection can be used to print into a specified file
Three Argument: i- option to turn on case insensitive filtering with second argument
	as input file path and third argument as the output file path. If the first argument
	is not -i then program prints invalid arguments and terminates
*/
	switch(argc){
		case 1 :
			input_fd = 0;
			output_fd = 1;
			parsestdio(input_fd,output_fd,case_insensitive);
			break;
		case 2 :
			switch(strcmp(argv[1],"-i")){
				case 0 :
					input_fd = 0;
					output_fd = 1;
					case_insensitive = true;
					parsestdio(input_fd,output_fd,case_insensitive);
					break;
				default :
					parsefilestdout(argv[1],1,case_insensitive);
			}
			break;
		case 3 :
			switch(strcmp(argv[1],"-i")){
				case 0 :
					case_insensitive = true;
					parsefilestdout(argv[2],1,case_insensitive);
					break;
				default :
					parsefile(argv[1],argv[2],case_insensitive);
			}
			break;
		case 4 :
			switch(strcmp(argv[1],"-i")){
				case 0 :
					case_insensitive = true;
					parsefile(argv[2],argv[3],case_insensitive);
					break;
				default :
					printf("Invalid option");
					exit(-1);
			}
			break;
	}
	return 0;
}
/*
*Reads from a file based on passed in fd number and stores the read in
*line into the passed in buffer. Uses a loop to read one byte at a time
*into the buffer until read encounters a new line character. Then it terminates
*loop. Returns the number of btyes read. if read returns -1, program
*terminates and returns -1;
*/
int parseline(int input_fd,char *buf){
	char c;
	int buf_pos = 0;
	int read_status = 1;
	while(read_status > 0){
		read_status = read(input_fd,&c,1);
		if(c == '\n'){
			buf[buf_pos] = '\0';
			break;
		}
		if(read_status == 0){
			return 0;
		}
		if(read_status == -1){
			printf("Read has encounted an error: %s\n",strerror(errno));
			exit(-1);
		}
		buf[buf_pos] = c;
		buf_pos++;
	}
	return buf_pos;
}
//Used for testing purpose, not used in the main program
void clearbuf(char *buf){
	for(int i = 0; i <strlen(buf); i++){
		buf[i] = 0;
	}
}
//Used for testing purpose, not used in the main program
void printstr(char *buf){
	int len = strlen(buf);
	int start = 0;
	while(start < len){
		printf("%c",buf[start]);
		start++;
	}
	printf("\n");
}
/*
*Checks if two lines from parseline() are the same, if bool case_insensitive
*is set to true then string checking is done without checking for upper or
*lower case, otherwise letter case will be checked. Returns true if lines are
*the same, otherwise returns false;
*/
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
/*
*Writes the line stored in buf to the file indicated by fd. After line is written
*a new line character is inserted as well. If write encounters an error, then
*error message is printed to console and program terminates. Returns the write functions
*return value, if theres no error then the return value is the number of bytes written.
*/
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
/*
*Takes in an input file path, output file path, and bool to determine case checking
*Opens input and output files and reads in the first line, then reads line 
*by line with parseline function and compares them with sameline function. 
*If lines are the same as well as the last written line then nothing is written.
*If the lines are different and buf1 line is the same as the last written
*line then buf2 line is written instead. If both lines are different and buf1
*line is different from last written line then both buf1 and buf2 lines are written.
*If open or close function encounters an error then error message is printed and
*program terminates.
*/
void parsefile(char *infile, char *outfile, bool case_insensitive){
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
		//**** Open file input/output for reading and writing *****//
	in_fd = open(infile,O_RDONLY);
	if(in_fd == -1){
		temp_errno = errno;
		printf("Unable to open input file \n");
		printf("Error: %s\n", strerror(errno));
		exit(-1);
	}
	out_fd = open(outfile,O_WRONLY | O_APPEND);
	if(out_fd == -1){
		temp_errno = errno;
		printf("Unable to open output file \n");
		printf("Error: %s\n", strerror(errno));
		exit(-1);
	}
	end_of_file = parseline(in_fd,buf1);
	if(end_of_file != 0){
		writeline(out_fd,buf1);
		strcpy(lastwrite,buf1);
		strcpy(buf1,empty);
		end_of_file = parseline(in_fd,buf1);
	}
	while(end_of_file != 0){
		end_of_file = parseline(in_fd,buf2);
		if(samelines(buf1,buf2,case_insensitive)){
			if(!samelines(lastwrite,buf1,case_insensitive)){
				writeline(out_fd,buf1);
				strcpy(lastwrite,buf1);
				strcpy(buf1,buf2);
			}
		}
		else{
			if(!samelines(lastwrite,buf1,case_insensitive)){
				writeline(out_fd,buf1);
				writeline(out_fd,buf2);
				strcpy(lastwrite,buf2);
				strcpy(buf1,buf2);
			}
			else{
				writeline(out_fd,buf2);
				strcpy(lastwrite,buf2);
				strcpy(buf1,buf2);
			}
		}
		strcpy(buf2,empty);
	}

		//***** Closes file after done reading *****//
	close_infile = close(in_fd);
	if(close_infile == -1){
		temp_errno = errno;
		printf("Closing file failed \n");
		printf("Error: %s\n", strerror(errno));
		exit(-1);
	}
		//***** Closes file after done writing *****//
	close_outfile = close(out_fd);
	if(close_outfile == -1){
		temp_errno = errno;
		printf("Closing file failed \n");
		printf("Error: %s\n", strerror(errno));
		exit(-1);
	}
}
/*
*Takes in fd instead of file paths for reading from stdin (fd = 0) and stdout (fd = 1)
*Opens input and output files and reads in the first line, then reads line 
*by line with parseline function and compares them with sameline function. 
*If lines are the same as well as the last written line then nothing is written.
*If the lines are different and buf1 line is the same as the last written
*line then buf2 line is written instead. If both lines are different and buf1
*line is different from last written line then both buf1 and buf2 lines are written.
*/
void parsestdio(int in_fd, int out_fd, bool case_insensitive){
	int end_of_file = 1;
	char buf1[2048];
	char buf2[2048];
	char lastwrite[2048];
	char empty[2048];

	end_of_file = parseline(in_fd,buf1);
	if(end_of_file != 0){
		writeline(out_fd,buf1);
		strcpy(lastwrite,buf1);
		strcpy(buf1,empty);
		end_of_file = parseline(in_fd,buf1);
	}
	while(end_of_file != 0){
		end_of_file = parseline(in_fd,buf2);
		if(samelines(buf1,buf2,case_insensitive)){
			if(!samelines(lastwrite,buf1,case_insensitive)){
				writeline(out_fd,buf1);
				strcpy(lastwrite,buf1);
				strcpy(buf1,buf2);
			}
		}
		else{
			if(!samelines(lastwrite,buf1,case_insensitive)){
				writeline(out_fd,buf1);
				writeline(out_fd,buf2);
				strcpy(lastwrite,buf2);
				strcpy(buf1,buf2);
			}
			else{
				writeline(out_fd,buf2);
				strcpy(lastwrite,buf2);
				strcpy(buf1,buf2);
			}
		}
		strcpy(buf2,empty);
	}

}
/*
*Takes in an inout file path and output fd for printing to stdout (fd = 0)
*Opens input and output files and reads in the first line, then reads line 
*by line with parseline function and compares them with sameline function. 
*If lines are the same as well as the last written line then nothing is written.
*If the lines are different and buf1 line is the same as the last written
*line then buf2 line is written instead. If both lines are different and buf1
*line is different from last written line then both buf1 and buf2 lines are written.
*/
void parsefilestdout(char *infile, int out_fd, bool case_insensitive){
	int in_fd;
	int end_of_file = 1;
	int close_infile;
	char buf1[2048];
	char buf2[2048];
	char lastwrite[2048];
	char empty[2048];
	int temp_errno;

	in_fd = open(infile,O_RDONLY);
	if(in_fd == -1){
		temp_errno = errno;
		printf("Unable to open input file \n");
		printf("Error: %s\n", strerror(errno));
		exit(-1);
	}
	end_of_file = parseline(in_fd,buf1);
	if(end_of_file != 0){
		writeline(out_fd,buf1);
		strcpy(lastwrite,buf1);
		strcpy(buf1,empty);
		end_of_file = parseline(in_fd,buf1);
	}
	while(end_of_file != 0){
		end_of_file = parseline(in_fd,buf2);
		if(samelines(buf1,buf2,case_insensitive)){
			if(!samelines(lastwrite,buf1,case_insensitive)){
				writeline(out_fd,buf1);
				strcpy(lastwrite,buf1);
				strcpy(buf1,buf2);
			}
		}
		else{
			if(!samelines(lastwrite,buf1,case_insensitive)){
				writeline(out_fd,buf1);
				writeline(out_fd,buf2);
				strcpy(lastwrite,buf2);
				strcpy(buf1,buf2);
			}
			else{
				writeline(out_fd,buf2);
				strcpy(lastwrite,buf2);
				strcpy(buf1,buf2);
			}
		}
		strcpy(buf2,empty);
	}
	if(close_infile == -1){
		temp_errno = errno;
		printf("Closing file failed \n");
		printf("Error: %s\n", strerror(errno));
		exit(-1);
	}

}
