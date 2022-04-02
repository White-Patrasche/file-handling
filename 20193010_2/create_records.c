#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define charMAX 30
// �ʿ��ϸ� header ���� �߰� ����
typedef struct student_record {
	char name[charMAX];
	int id;
	char major[charMAX]; 
}record;
//
// input parameters: �л� ���ڵ� ��, ���ڵ� ����
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
	// ����ڷκ��� �Է� ���� ���ڵ� �� ��ŭ�� ���ڵ� ������ �����ϴ� �ڵ� ����
	
	// ���Ͽ� '�л� ���ڵ�' ������ �� ���� ����
	// 1. ���ڵ��� ũ��� ������ 200 ����Ʈ�� �ؼ�
	// 2. ���ڵ� ���Ͽ��� ���ڵ�� ���ڵ� ���̿� � �����͵� ���� �ȵ�
	// 3. ���ڵ忡�� ������ �����͸� �����ص� ����
	// 4. ���� n���� ���ڵ带 �����ϸ� ���� ũ��� ��Ȯ�� 200 x n ����Ʈ�� �Ǿ�� ��

	return 0;
}
