/******
TODO: 
-(DONE)Parsing arguments
-(DONE)setting up threads
-(DONE)thread logic 
-(DONE)synchronization on lines_read data access
-(DONE)joining threads
-(DONE)appropriate stdout messages according to homework specification
-(DONE)add error checking
-restructure code
-final test to ensure code works
-comments
-summary comment

LEFTOFF:
4/11/2020
(SOLVED)Getting segmentation faults I believe in either the parse_line function that the threads are running on
or something to do with the pthread_join calls.(SOLUTION)I was passing pointers to memory address instead of passing
pointers to a variable. It caused the function fopen to try to open a file with a memory address instead of a char* 
to a file name.
******/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#define line_size 10000
#define checkpoint 0

// Global variable of lines scanned and string pattern
int lines_read = 0;
char* pattern;
// Global lock for use by threads to accress lines_read
pthread_mutex_t lines_read_lock = PTHREAD_MUTEX_INITIALIZER;

// Threat function
void* parse_file(void *arg){

	if(checkpoint)
		printf("Checkpoint: start of thread\n");
	char* filename = arg;

	if(checkpoint)
		printf("Checkpoint: filename: %s\n",filename);
	int* lines_matched = (int*)malloc(sizeof(int*));
	*lines_matched = (int)malloc(sizeof(int));
	*lines_matched = 0;
	FILE* input = fopen(filename,"r");
	if(input == NULL){
		perror("Unable to open file");
		pthread_exit(lines_matched);
	}
	char line[line_size];
	int file_lines_read = 0;
	char* get_line_status = "";
	get_line_status = fgets(line,line_size,input);
	while(get_line_status != NULL){
			file_lines_read++;
		if(strstr(line,pattern) != NULL){
			*lines_matched += 1;
			printf("%s: %s",filename,line);
		}
		get_line_status = fgets(line,line_size,input);
	}
	pthread_mutex_lock(&lines_read_lock);
	lines_read += file_lines_read;
	pthread_mutex_unlock(&lines_read_lock);
	printf("--%s has %d matched lines\n",filename, *lines_matched);

	if(checkpoint)
		printf("Checkpoint: thread finish\n");

	pthread_exit(lines_matched);
}

int main(int argc, char* argv[]){
/* Argument checking */
	if(argc < 3){
		printf("invalid number of arguments\n");
		printf("usage: [Pattern] [FileName1] [FileName2] ... [FileNameN]\n"); 
		exit(EXIT_FAILURE);
	}
/* Argument parsing */

	if(checkpoint)
		printf("Checkpoint: Before argument parsing\n");

	pattern = argv[1];

	if(checkpoint)
		printf("Checkpoint: pattern stored: '%s'\n", pattern);

	int num_files = argc - 2;

	if(checkpoint)
		printf("Checkpoint: num of files passed in: %d\n", num_files);

	pthread_t ids[num_files];
	int create_thread_status = 0;
/* Thread creation */
	for(int i = 0; i < num_files; i++){

		if(checkpoint)
			printf("Checkpoint: Before creating thread#%d: passing in file: %s\n", i+1, argv[i+2]);

		pthread_create(&ids[i],NULL,parse_file,argv[i+2]);
		if(create_thread_status)
			perror("pthread_create: error\n");
	}
	int* retval;
	int thread_join_status;
	int lines_matched = 0;
	for(int i = 0; i < num_files; i++){

		if(checkpoint)
			printf("Checkpoint: before joining thread %d\n", i);		

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
