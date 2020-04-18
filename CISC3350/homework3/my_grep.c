/*****************************
Eric Y. U Huang
CISC 3350 - TR3 Spring 2020
Professor Y. Xiang
Homework 3

This program is compiled with the 'gcc -Wall -pthread -o my_grep my_grep.c' using gcc version (Debian 8.3.0-6) 8.3.0
This program emulates the basic feature of linux grep command by searching lines in one or more files that contains
the user inputted pattern. The program parses the command line arguments by:
./my_grep [Pattern] [FileName1] [FileName2] ... [FileNameN]
with Pattern being the string being searched for inside the files FileNameN. The program first parses the command 
line arguments. If the number of command line arguments is less than 3, the program will terminate after stating
not enough arguments. If proper number of arguments are given, the program will store the Pattern given by user
as a global variable. The total number of lines_read from all files and a mutex lock, lines_read_lock, for
accessing the variable are also stored as global variables. Program then creates a thread per each file given by user
and passes the FileName to the threads. Each threads will attempt to open a file based on the passed in FileName.
The threads will than read a line and search for the Pattern in each line. Every line read in will increment the
local variable, file_lines_read. The threads will print out the line if the Pattern is found in the line and
increment a counter for lines_matched. After all the lines are read in a file, the thread will add the total
number of file_lines_read to the global variable lines_read by obtaining the mutex lock, lines_read_lock, and
releasing it when it's done adding to it. The thread then returns to the main thread/process the number of
lines_matched when it exits. Meanwhile the main thread/process waits for all the threads to finish by calling
pthread_join in a for loop. It adds the thread return value to lines_matched and prints the return value of each
pthread_join which is the lines_matched. After all the threads are finished, the main thread/process prints out
the number of lines_matched and total number of lines read from global variable lines_read.
*****************************/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#define line_size 10000

// Global variable of total lines scanned and string pattern
int lines_read = 0;
char* pattern;
// Global lock for use by threads to accress lines_read
pthread_mutex_t lines_read_lock = PTHREAD_MUTEX_INITIALIZER;

// Threat function
void* parse_file(void *arg){
	char* filename = arg;
/* 
Since I need the return value to exist after the function returns,
I allocate memory in the free store to store the number of lines_matched.
*/
	int* lines_matched = (int*)malloc(sizeof(int*));
	*lines_matched = (int)malloc(sizeof(int));
	*lines_matched = 0;
// Opens file stream
	FILE* input = fopen(filename,"r");
	if(input == NULL){
		perror("Unable to open file");
		pthread_exit(lines_matched);
	}
	char line[line_size];
	int file_lines_read = 0;
	char* get_line_status = "";
// Reads and searches for the Pattern
	get_line_status = fgets(line,line_size,input);
	while(get_line_status != NULL){
			file_lines_read++;
		if(strstr(line,pattern) != NULL){
			*lines_matched += 1;
			printf("%s: %s",filename,line);
		}
		get_line_status = fgets(line,line_size,input);
	}
// Obtains lock and increments global variable
	pthread_mutex_lock(&lines_read_lock);
	lines_read += file_lines_read;
	pthread_mutex_unlock(&lines_read_lock);
// Releases lock
	printf("--%s has %d matched lines\n",filename, *lines_matched);
	pthread_exit(lines_matched);
}

int main(int argc, char* argv[]){
// Argument checking
	if(argc < 3){
		printf("invalid number of arguments\n");
		printf("usage: [Pattern] [FileName1] [FileName2] ... [FileNameN]\n"); 
		exit(EXIT_FAILURE);
	}
// Argument parsing
	pattern = argv[1];
	int num_files = argc - 2;
	pthread_t ids[num_files];
	int create_thread_status = 0;
// Thread creation
	for(int i = 0; i < num_files; i++){
		pthread_create(&ids[i],NULL,parse_file,argv[i+2]);
		if(create_thread_status)
			perror("pthread_create: error\n");
	}
	int* retval;
	int thread_join_status;
	int lines_matched = 0;
// Waits on all the threads
	for(int i = 0; i < num_files; i++){
		thread_join_status = pthread_join(ids[i], &retval);
		if(thread_join_status){
			perror("pthread_join: error\n");
		}
		else{
			lines_matched += *retval;
			printf("[main] Thread #%d returned with value: %d\n", i+1, *retval);
		}
	}
	printf("Total of %d matched lines among total of %d lines scanned\n",lines_matched,lines_read);
	return 0;
}
