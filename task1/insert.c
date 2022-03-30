#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
	if(argc != 4) {
		fprintf(stderr, "your excution parameter is not enough or too many!\n");
		exit(1);
	}
	FILE* fp1;
	long long size;
	char buf[BUFFER_SIZE];
	
	if((fp1 = fopen(argv[3], "r+")) == NULL) {
		fprintf(stderr, "open error for %s!\n", argv[3]);
		exit(1);
	}
	fseek(fp1, 0, SEEK_END);
	size = ftell(fp1);
	if(size <= atoll(argv[1])) { //if eof
		fseek(fp1, 0, SEEK_END);
		fwrite(argv[2], sizeof(char), strlen(argv[2]), fp1);
	}
	else {
		FILE* fp2;
		char* fileName = "TEMP.tmp";
		if((fp2 = fopen(fileName, "w+")) == NULL){
			fprintf(stderr, "open error for %s!\n", fileName);
			exit(1);
		} //make temp file
		fseek(fp1, 0, SEEK_SET);
		for(long long i=0; i<=atoll(argv[1]); i++) {
			memset(buf, 0, sizeof(buf));
			fread(buf, sizeof(char), 1, fp1);
			fwrite(buf, sizeof(char), 1, fp2);
		}
		fwrite(argv[2], sizeof(char), strlen(argv[2]), fp2);
		while(feof(fp1) == 0) {
			memset(buf, 0, sizeof(buf));
			size = fread(buf, sizeof(char), BUFFER_SIZE-1, fp1);
			if(size < BUFFER_SIZE) {
				fwrite(buf, sizeof(char), size, fp2);
				break;
			}
			fwrite(buf, sizeof(char), strlen(buf), fp2);
		}
		rewind(fp1);
		rewind(fp2);
		while(fgets(buf, BUFFER_SIZE, fp2) != NULL) { //it's bigger than original data, so it't not problem
			fputs(buf, fp1);
		}
		fclose(fp2);
		remove(fileName);
	}

	fclose(fp1);
	exit(0);
}
