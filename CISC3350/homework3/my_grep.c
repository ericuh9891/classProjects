/******
TODO: 
-Parsing arguments
-setting up threads
-thread logic 
-synchronization on lines_read data access
-joining threads
-appropriate stdout messages according to homework specification
-error checking
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
#include <unistd.h> // for sleep function

#define line_size 10000
#define checkpoint 1

// Global variable of lines scanned and string pattern
int lines_read = 0;
char* pattern;
// Global lock for use by threads to accress lines_read
pthread_mutex_t lines_read_lock = PTHREAD_MUTEX_INITIALIZER;

// Threat function
void* parse_file(void *arg){
	if(checkpoint)
		printf("start of thread\n");
	char* filename = arg;
	if(checkpoint)
		printf("filename: %s\n",filename);
	char line[line_size];
	char* get_line_status = "";
	FILE* input = fopen(filename,"r");
	int* lines_matched = (int*)malloc(sizeof(int));
	lines_matched = 0;
	int file_lines_read = 0;
	get_line_status = fgets(line,line_size,input);
	while(get_line_status != NULL){	
		if(get_line_status != NULL){
			file_lines_read++;
		}
		if(strstr(line,pattern) != NULL){
			lines_matched++;
			printf("%s: %s",filename,line);
		}
		get_line_status = fgets(line,line_size,input);
	}
	
	pthread_mutex_lock(&lines_read_lock);
	lines_read += file_lines_read;
	pthread_mutex_unlock(&lines_read_lock);
	printf("--%s has %d matched lines\n",filename, *lines_matched);
	if(checkpoint)
		printf("thread finish\n");
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
		printf("checkpoint: Before argument parsing\n");
	pattern = argv[1];
	printf("pattern stored: '%s'\n", pattern);
	int num_files = argc - 2;
	printf("num of files passed in: %d\n", num_files);
	pthread_t ids[num_files];
	int create_thread_status = 0;
/* Thread creation */
	for(int i = 0; i < num_files; i++){
		if(checkpoint)
			printf("checkpoint: Before creating thread %d\n", i);
		printf("passing in file: %s\n", argv[i+2]);
		pthread_create(&ids[i],NULL,parse_file,argv[i+2]);
		if(create_thread_status){
			printf("pthread_create: error\n");
			strerror(create_thread_status);
		}
	}
	int* retval;
	int thread_join_status;
	for(int i = 0; i < num_files; i++){
		if(checkpoint)
			printf("checkpoint: before joining thread %d\n", i);		
		thread_join_status = pthread_join(ids[i], (void**)retval);
		if(thread_join_status){
			printf("pthread_join error: %d\n", thread_join_status);
			strerror(thread_join_status);
		}
		printf("[main] Thread #%d returned with value: %d\n", i, *(int*)retval); 
	}
	printf("Total lines read: %d\n",lines_read);
	return 0;
}
