#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
	
	char buf[BUFFER_SIZE];

	if(argc != 4) {
		fprintf(stderr, "your excution parameter is not enough or too many!\n");
		exit(1);
	}
	FILE* fp;
	if((fp = fopen(argv[3], "r+")) == NULL) {
		fprintf(stderr, "fopen error for %s!\n", argv[3]);
		exit(1);
	}
	long long offset = atoll(argv[1]);
	long long byte = atoll(argv[2]);
	long long size;
	fseek(fp, 0, SEEK_END);
	size = ftell(fp); //count file size
	fseek(fp, 0, SEEK_SET);
	clearerr(fp); //eof flag off

	if(byte == 0) {
		fclose(fp);
		exit(0);
	}
	long long firstRead;
	if(byte < 0) {
		byte = -byte;
		firstRead = offset - byte;
	}
	else {
		firstRead = offset;
	}
	if(firstRead <= 0) {
		firstRead = 0;
		byte = offset;
	}

	FILE* fpCopy;
	char* fileName = "TEMP.tmp";
	if((fpCopy = fopen(fileName, "w+")) == NULL) {
		fprintf(stderr, "open error for %s!\n", fileName);
		exit(1);
	}

	for(long long i=0; i<=firstRead; i++) {
		memset(buf, 0, sizeof(buf));
		fread(buf, sizeof(char), 1, fp);
		fwrite(buf, sizeof(char), 1, fpCopy);
	}
	fread(buf, sizeof(char), byte, fp);
	while(feof(fp) == 0) {
		memset(buf, 0, sizeof(buf));
		size = fread(buf, sizeof(char), BUFFER_SIZE, fp);
		if(size < BUFFER_SIZE) {
			fwrite(buf, sizeof(char), size, fpCopy);
			break;
		}
		fwrite(buf, sizeof(char), strlen(buf), fpCopy);
	}
	rewind(fpCopy);
	freopen(argv[3], "w+", fp);
	while(fgets(buf, BUFFER_SIZE, fpCopy) != NULL) {
		fputs(buf, fp);
	}
	fclose(fpCopy);
	remove(fileName);
	fclose(fp);
	exit(0);
}
