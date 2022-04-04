#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

#define charMAX 32

typedef struct student_record {
	char name[charMAX]; //32
	int id; //4
	char major[charMAX]; //32
	char dummy[200-charMAX*2-sizeof(int)]; //32
}record;

int main(int argc, char **argv) {
	int fd;
	clock_t start, end;
	if(argc < 2) {
		fprintf(stderr, "Your input is not enough to excution.");
		exit(1);
	}
	else if(argc > 2) {
		fprintf(stderr, "Your input is not too many to excution.");
		exit(1);
	}
	//open record file
	if((fd = open(argv[1], O_RDONLY)) < 0) {
		fprintf(stderr, "open error for %s.", argv[1]);
		exit(1);
	}

	off_t file_size = lseek(fd, 0, SEEK_END); //check file size
	lseek(fd, 0, SEEK_SET); //file current position

	start = clock();
	int recordSize = sizeof(record);
	for(int i=0; i<(file_size/recordSize); i++) {
		record Data;
		read(fd, &Data, recordSize);
	}
	close(fd);
	end = clock();
	printf("%ld usec\n", end-start);

	return 0;
}
