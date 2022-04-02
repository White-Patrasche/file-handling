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
	char dummy[charMAX]; //32
}record;

int main(int argc, char **argv) {
	int fd;
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
	clock_t start, end;
	start = clock();
	off_t file_size = lseek(fd, 0, SEEK_END); //check file size
	lseek(fd, 0, SEEK_SET); //file current position
	for(int i=0; i<file_size; i+=sizeof(record)) {
		record Data;
		read(fd, &Data, sizeof(record));
		/*
		printf("Name : %s, ID : %d, Major : %s\n", Data.name, Data.id, Data.major);
		*/
	}
	close(fd);
	end = clock();
	printf("%ld usec\n", end-start);

	return 0;
}
