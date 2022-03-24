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
	size = ftell(fp);
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

	FILE* fpCopy;
	char* fname = "TEMP.tmp";
	fpCopy = fopen(fname, "w+");
	memset(buf);
	for(int i=0; i<firstRead; i++) {
		fread(
	}

}
