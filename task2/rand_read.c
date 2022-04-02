#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


#define SUFFLE_NUM 20193010	
#define charMAX 32

void GenRecordSequence(int *list, int n);
void swap(int *a, int *b);


typedef struct student_record {
	char name[charMAX];
	int id;
	char major[charMAX];
	char dummyData[charMAX];
}record;

int main(int argc, char **argv)
{
	int fd;
	if(argc < 2) {
		fprintf(stderr, "Your input is not enough to excution.\n");
		exit(1);
	}
	else if(argc > 2) {
		fprintf(stderr, "Your input is too many to excution.\n");
		exit(1);
	}
	//argv[1] is record file name

	int *read_order_list;
	int num_of_records;
	if((fd = open(argv[1], O_RDONLY)) < 0) {
		fprintf(stderr, "open error for %s.\n", argv[1]);
		exit(1);
	}
	num_of_records = lseek(fd, 0, SEEK_END) / 200;

	GenRecordSequence(read_order_list, num_of_records);
	time_t start, end;
	start = clock();
	for(int i=0; i<num_of_records; i++) {
		record Data;
		lseek(fd, read_order_list[i]*200, SEEK_SET);
		read(fd, &Data, sizeof(Data));
	}
	close(fd);
	end = clock();
	printf("%ld usec\n",end - start);

	return 0;
}

void GenRecordSequence(int *list, int n)
{
	int i, j, k;

	srand((unsigned int)time(0));

	for(i=0; i<n; i++)
	{
		list[i] = i;
	}
	
	for(i=0; i<SUFFLE_NUM; i++)
	{
		j = rand() % n;
		k = rand() % n;
		swap(&list[j], &list[k]);
	}

	return;
}

void swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;

	return;
}
