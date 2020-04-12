#include <pthread.h>
#include <stdio.h>

struct files_scanner{
	char* filename;
	pthread_mutex_t mutex_lock;
};

int main(){
	struct files_scanner file1;
	file1.filename = "myfile";
	//pthread_mutex_init(&file1.mutex_lock, NULL);	
	printf("%s\n", file1.filename);
	return 0;
}
