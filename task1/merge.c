#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {

	char buf[BUFFER_SIZE];
	ssize_t rd_size;
	int fd1, fd2, fd3;

	if(argc != 4) {
		fprintf(stderr, "your excution parameter is not enough or too many\n");
		exit(1);
	}

	if((fd1 = open(argv[1], O_RDONLY)) < 0) {
		fprintf(stderr, "open error for %s\n", argv[1]);
		exit(1);
	}
	if((fd2 = open(argv[2], O_RDONLY)) < 0) {
		fprintf(stderr, "open error for %s\n", argv[2]);
		exit(1);
	}
	fd3 = open(argv[3], O_RDWR | O_CREAT | O_TRUNC, 0666);
	
	memset(buf, 0, sizeof(buf));
	while((rd_size = read(fd1, buf, BUFFER_SIZE-1)) > 0) {
		write(fd3, buf, rd_size);
		memset(buf, 0, sizeof(buf));
	}
	memset(buf, 0, sizeof(buf));
	while((rd_size = read(fd2, buf, BUFFER_SIZE-1)) > 0) {
		write(fd3, buf, rd_size);
		memset(buf, 0, sizeof(buf));
	}
	close(fd1);
	close(fd2);
	close(fd3);
	exit(0);
}
