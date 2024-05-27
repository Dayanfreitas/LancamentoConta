
#include <stdio.h>
#include <stdlib.h>

FILE* openFile(const char * fileName, const char * mode){
	FILE *file = fopen(fileName, mode);
	if(file == NULL){
		printf("Erro ao abrir o arquivo %s\n", fileName);
		exit(EXIT_FAILURE);
	}
	return file;
}

void printFileContent(FILE *f) {
	int c;

	while ((c = fgetc(f)) != EOF) {
		printf("%c",c);
	}
}
