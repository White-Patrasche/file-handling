#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[]) {
	if(argc != 4) {
		fprintf(stderr, "your excution parameter is not enough or too many!\n");
		exit(1);
	}
	int fd;
	off_t cur;
	if((fd = open(argv[3], O_RDWR)) < 0) {
		fprintf(stderr, "open error for %s!\n", argv[3]);
		exit(1);
	}
	if((cur = lseek(fd, atoi(argv[1]), SEEK_SET)) < 0) {
		fprintf(stderr, "lseek error\n");
		exit(1);
	}

	if(cur != lseek(fd, 1, SEEK_CUR)) { //not EOF
	}
	else {
	}


	close(fd);
	exit(0);
}
