#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/display.h"
#include "../include/date_utils.h"
#include "../include/accounting.h"

#define  NOME_ARQUIVO "financial_movement.txt"
#define  MODE_FILE_A "a"
#define  MODE_FILE_READ "r"

typedef struct {
	int dia;
	int mes;
	int ano; 
} date; 

struct ficha_de_conta{
	date data;
 	char descricao[100];  
	float valor;
};

struct ficha_de_conta lancamento;

void accountant();

void readIncoming();
void readExpense();

void saveMovement(int movimento);


int main(){
	accountant();
	return EXIT_SUCCESS;
}

void accountant(){
	char choice[10];	
	int optionsChoice;
	
	pause();
	showOptions();
	fgets(choice, sizeof(choice), stdin);
	optionsChoice = atoi(choice);

	clean();

	if (isIncoming(optionsChoice)) {
		displayIncoming();
		readIncoming();
		saveMovement(optionsChoice);
	} else if (isExpense(optionsChoice)) {
		displayExpense();
		readExpense();
		saveMovement(optionsChoice);
	} else if (isSeeListMovements(optionsChoice)) {
		FILE *file;
		int c;
		
		displayMovement();

		file = fopen(NOME_ARQUIVO, MODE_FILE_READ);
		
		if (file == NULL) {
			printf("Arquivo não encontrado");
			line();

			pause();
			return;
		}

		while (!feof(file)) {
			c = fgetc(file);
			printf("%c",c);
		}

		fclose(file);
		printf("%c\n", c);
		pause();
	} else if (isExit(optionsChoice)) {
		saveMovement(optionsChoice);
	} else {
		clean();
		
		printf("Opção inválida!");
		line();
		pause();
	}

	fflush(stdin);
	accountant();
}

void readIncoming() {
	printf("Digite a descrição:");
	scanf("%s", lancamento.descricao);
	fflush(stdin);
	printf("Digite o valor:");
	scanf("%f", &lancamento.valor);
}

void readExpense() {
	printf("Digite a descrição:");
	scanf("%s", lancamento.descricao);
	fflush(stdin);
	printf("Digite o valor:");
	scanf("%f", &lancamento.valor);
}

void saveMovement(int movimento) {
	float static totalReceita = 0;
	float static totalDespesa = 0;
	float static total = 0;
	
	FILE *fp;
	fp = fopen (NOME_ARQUIVO, MODE_FILE_A);

	if(isIncoming(movimento)){
		char *line = cseparetor(33);	
		
		fprintf(fp,"%s\n", line);
		fprintf(fp,"MOVIMENTECAO: Receita\n");       
		free(line);

		// DESCRIÇÃO DO MOVIMENTO
		fprintf(fp, "Data : %s", dateNow());
		fprintf(fp, "\t\tDESCRICAO: %s", lancamento.descricao);
		fprintf(fp, "\t\tVALOR: %.2f\n", lancamento.valor);

		// CALCULA O TOTAL
		// Salvar no arquivo	
		totalReceita += lancamento.valor; 
		total = totalReceita - totalDespesa;
		fprintf(fp, "TOTAL RECEITA:%.2f",totalReceita);	
		fprintf(fp, "\tTOTAL DESPESA:%.2f",totalDespesa);	
		fprintf(fp, "\tTOTAL:%.2f\n",total);	
	}
	else if (isExpense(movimento)){
		char *separetor = cseparetor(33);	

		fprintf(fp, "%s\n", separetor);
		fprintf(fp,"MOVIMENTECAO: Despesa\n");
		free(separetor);

		// DESCRIÇÃO DO MOVIMENTO
		fprintf(fp, "Data : %s", dateNow());
		fprintf(fp, "\t\tDESCRICAO: %s", lancamento.descricao);
		fprintf(fp, "\t\tVALOR: %.2f\n", lancamento.valor);

		// CALCULA O TOTAL
		// Salvar no arquivo	
		totalDespesa += lancamento.valor;
		total = totalReceita - totalDespesa;
		fprintf(fp, "TOTAL RECEITA:%.2f",totalReceita);	
		fprintf(fp, "\tTOTAL DESPESA:%.2f",totalDespesa);	
		fprintf(fp, "\tTOTAL:%.2f\n",total);	
	}else if (isExit(movimento)){	
		char *separetor = cseparetor(33);

		total = totalReceita - totalDespesa;
		fprintf(fp, "%s\n", separetor);
		fprintf(fp, "TOTAL: %.2f\n", total);	
		fprintf(fp, "%s\n", separetor);
		free(separetor);

		fclose(fp);
		exit(EXIT_SUCCESS);
	}

	fclose(fp);	
}