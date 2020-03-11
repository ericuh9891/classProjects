#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

#define line_size 2621440

int main(int argc, char **argv){

	int pr_limit;
	int pr_count;
	char buf[line_size];
	if(argc != 2){
		printf("invalid number of arguments");
		exit(1);
	}
	if(pr_limit = atoi(argv[1]) == 0){
		printf("invalid argument for number of processes");
		exit(1);
	}
	fgets(buf, line_size, stdin);
	printf("%s%c",buf,'\0');
	return 0;
}
