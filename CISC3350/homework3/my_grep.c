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
Getting segmentation faults I believe in either the parse_line function that the threads are running on
or something to do with the pthread_join calls.
******/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for sleep function

#define line_size 2621440
// Global variable of lines scanned and string pattern
int lines_read = 0;
char* pattern;
// Global lock for use by threads to accress lines_read
pthread_mutex_t lines_read_lock = PTHREAD_MUTEX_INITIALIZER;

void* parse_file(void *arg){
	char* filename = (char*)arg;
	printf("filename: %s\n",filename);
	char line[line_size];
	char* get_line_status = "";
	FILE* input = fopen(filename,"r");
	int lines_matched = 0;
	int file_lines_read = 0;
	get_line_status = fgets(line,line_size,input);
	do{
		if(!strstr(line,pattern))
			lines_matched++;
		else{
			printf("%s: %s\n",filename,line);
			lines_read++;
		}
/*
		if(strstr(line,pattern)){
			printf("%s: %s\n",filename,line);
		}
*/
	}while(get_line_status != NULL);
	printf("lines matched: %d\n", lines_matched);
	printf("lines read: %d\n", file_lines_read);
	printf("thread finish\n");
	pthread_exit(NULL);
}

int main(int argc, char** argv){
/* Argument checking */
	if(argc < 3){
		printf("invalid number of arguments\n");
		printf("usage: [Pattern] [FileName1] [FileName2] ... [FileNameN]\n"); 
		exit(EXIT_FAILURE);
	}
	printf("checkpoint: Before argument parsing\n");
/* Argument parsing */
//	strcpy(pattern,argv[1]);
	pattern = argv[1];
	int num_files = argc - 2;
	pthread_t ids[num_files];
	int create_thread_status = 0;
/* Opening files */
	printf("checkpoint: before thread creation\n");
	for(int i = 0; i < num_files; i++){
		printf("checkpoint: Before creating thread %d\n", i);
		printf("passing in file: %s\n", argv[i+2]);
		pthread_create(&ids[i],NULL,parse_file,&argv[i+2]);
		if(create_thread_status){
			printf("pthread_create: error\n");
			strerror(create_thread_status);
		}
	}
	int ret = 0;
	for(int i = 0; i < num_files; i++){
		printf("checkpoint: before joining thread %d\n", i);		
		ret = pthread_join(ids[i], NULL);
		if(ret){
			printf("pthread_join error: %d\n", ret);
			strerror(ret);
		}
	}
	return 0;
}
