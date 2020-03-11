//Adding text for testing purposes

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 2048;

int main(int argc, char *argv[]){
/*
	int read_status;
	char* buf[2048];
	int num_written;
	read_status = read(0,buf,2048);
	num_written = write(1,buf,2048);

*/
	char buf1[2048] = "Hello";
	char buf2[2048] = "GoodBye";
	char empty[2048];
/*
	printf("%s\n", buf1);
	printf("%s\n", buf2);
	printf("After swap\n");
	strcpy(buf1,buf2);
	printf("%s\n", buf1);
	printf("%s\n", buf2);

	int write_state;
	int fd;
	fd = open("results",O_WRONLY | O_APPEND);
	write_state = write(fd,buf1,strlen(buf1));
	printf("Return of write is %i and error is: %s\n",write_state,strerror(errno));
*/

	printf("%s\n",buf1);
	printf("%s\n",buf2);
	strcpy(buf2,empty);
	printf("%s\n",buf1);
	printf("%s\n",buf2);
	return 0;
}
