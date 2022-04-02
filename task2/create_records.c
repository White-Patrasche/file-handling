#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define charMAX 32

typedef struct student_record {
	char name[charMAX]; //32
	int id; //4
	char major[charMAX]; //32
	char dummydata[charMAX]; //32
	char dummy[100];
}record;

int main(int argc, char **argv)
{
	int fd;
	
	if(argc < 3) {
		fprintf(stderr, "Your input is not enough to excution.");
		exit(1);
	}
	else if (argc > 3) {
		fprintf(stderr, "Your input is too many to excution.");
		exit(1);
	}
	//if argc == 3, it's correct
	//argv[1] = records, argv[2] = filename
	if((fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC)) < 0) {
		fprintf(stderr, "open error for %s", argv[2]);
		exit(1);
	}
	for(long long i=1; i<=atoll(argv[1]); i++) { //
		record inputData;
		strcpy(inputData.name, "sanghyeon");
		inputData.id = 20193010+i;
		strcpy(inputData.major, "CSE");
		strcpy(inputData.dummydata, "");
		//write(fd, &inputData, 200); //200 bytes records
		write(fd, &inputData, sizeof(record));
	}
	record T;
	close(fd);

	return 0;
}
