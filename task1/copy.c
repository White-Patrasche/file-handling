#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 10
int main(int argc, char* argv[]) {
	char buf[BUFFER_SIZE];
	FILE* origin;
	FILE* copy;
	if(argc != 3) {
		fprintf(stderr, "excution parameter is not enough\n");
		exit(1);
	}
	if((origin = fopen(argv[1], "r+")) == NULL) {
		fprintf(stderr, "open error for %s\n", argv[1]);
		exit(1);
	}
	copy = fopen(argv[2], "w+");
	
	memset(buf, 0, BUFFER_SIZE);
	int size = 0;
	while(feof(origin) == 0) {
		size = fread(buf, sizeof(char), BUFFER_SIZE, origin);
		if(size < BUFFER_SIZE) {
			fwrite(buf, sizeof(char), size, copy);
			break;
		}
		fwrite(buf, sizeof(buf), 1, copy);
		memset(buf, 0, sizeof(buf));
	}


	fclose(origin);
	fclose(copy);
	exit(0);
}
