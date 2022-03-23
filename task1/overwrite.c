#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
	char buf[BUFFER_SIZE];
	if(argc != 4) {
		fprintf(stderr, "your excution parameter is not enough or too many\n");
		exit(1);
	}
	int fd;
	if((fd = open(argv[3], O_RDWR)) < 0) {
		fprintf(stderr, "open error for %s\n", argv[3]);
		exit(1);
	}
	if(lseek(fd, atoi(argv[1]), SEEK_SET) < 0) {
		fprintf(stderr, "file seek error\n");
		exit(1);
	}
	strcpy(buf, argv[2]);

	write(fd, buf, strlen(buf));
	close(fd);
	exit(1);
}
