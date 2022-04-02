#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define charMAX 30
// 필요하면 header 파일 추가 가능
typedef struct student_record {
	char name[charMAX];
	int id;
	char major[charMAX]; 
}record;
//
// input parameters: 학생 레코드 수, 레코드 파일
//
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
	for(int i=1; i<=atoi(argv[1]); i++) { //
		record inputData;
		strcpy(inputData.name, "sanghyeon");
		inputData.id = 20193010+i;
		strcpy(inputData.major, "CSE");
		write(fd, inputData, 200); //200 bytes records
	}
	close(fd);
	// 사용자로부터 입력 받은 레코드 수 만큼의 레코드 파일을 생성하는 코드 구현
	
	// 파일에 '학생 레코드' 저장할 때 주의 사항
	// 1. 레코드의 크기는 무조건 200 바이트를 준수
	// 2. 레코드 파일에서 레코드와 레코드 사이에 어떤 데이터도 들어가면 안됨
	// 3. 레코드에는 임의의 데이터를 저장해도 무방
	// 4. 만약 n개의 레코드를 저장하면 파일 크기는 정확히 200 x n 바이트가 되어야 함

	return 0;
}
