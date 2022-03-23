#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
	int fd;
	off_t fsize;
	char buf[BUFFER_SIZE];
	if(argc != 4) {
		fprintf(stderr, "your input is not enough or too many!\n");
		exit(1);
	}

	if((fd = open(argv[3], O_RDONLY)) < 0) {
		fprintf(stderr, "open error for %s", argv[3]);
		exit(1);
	}
	int offset = atoi(argv[1]);
	int byte = atoi(argv[2]);
	if(byte == 0) {
		close(fd);
		exit(0);
	}
	else if(byte < 0) {
		byte = -byte;
		if((fsize = lseek(fd, offset - byte, SEEK_SET)) < 0) {
			fprintf(stderr, "lseek error\n");
			exit(1);
		}
	}
	else {
		if((fsize = lseek(fd, offset, SEEK_SET)) < 0) {
			fprintf(stderr, "lseek error\n");
			exit(1);
		}
	}
	memset(buf, 0, sizeof(buf));
	if(read(fd, buf, byte) < 0) {
		fprintf(stderr, "reading error\n");
		exit(1);
	}
	printf("start printing data\n%s\nprinting ended\n", buf);
	close(fd);
	exit(0);
}
