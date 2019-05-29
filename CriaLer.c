#include <stdio.h> 
#include <conio.h>

int main(){
    FILE *fp;
    
    //Escrever
	fp = fopen ("arquivo.txt", "w");
	fprintf(fp,"=================================\n");
	fclose(fp);
    
    //Ler
    int c;
    fp = fopen("arquivo.txt","r");
    while(!feof(fp)) {
        c = fgetc(fp);
        printf("%c",c);
    }
    fclose(fp);
    return 0;    
}