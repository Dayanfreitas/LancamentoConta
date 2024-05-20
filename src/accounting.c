#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/display.h"
#include "../include/date_utils.h"

#define  NOME_ARQUIVO "financial_movement.txt"
#define  MODO_ARQUIVO "a"

#define OP_INCOMING 1
#define OP_EXPENSE 2
#define OP_SEE_LIST 3

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

int isIncoming(int opc);
int isExpense(int opc);
int isExit(int opc);

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

		file = fopen(NOME_ARQUIVO, "r");
		
		if (file == NULL) {
			printf("Arquivo não encontrado\n");
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
		
		printf("Opção inválida!\n");
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

int isIncoming(int opc) {
	return opc == OP_INCOMING;
}

int isExpense(int opc) {
	return opc == OP_EXPENSE;
}

int isSeeListMovements(int opc) {
	return opc == OP_SEE_LIST;
}

int isExit(int opc) {
	return opc == EXIT_SUCCESS;
}

void saveMovement(int movimento) {
	float static totalReceita = 0;
	float static totalDespesa = 0;
	float static total = 0;
	
	FILE *fp;
	fp = fopen (NOME_ARQUIVO, MODO_ARQUIVO);

	if(isIncoming(movimento)){
		totalReceita += lancamento.valor; 
		fprintf(fp,"=================================\n");
		fprintf(fp,"MOVIMENTECAO:Receita\n");       
		
		// DESCRIÇÃO DO MOVIMENTO
		fprintf(fp, "Data : %s", dateNow());
		fprintf(fp, "\t\tDESCRICAO: %s",lancamento.descricao);
		fprintf(fp, "\t\tVALOR: %.2f\n",lancamento.valor);

		// CALCULA O TOTAL
		// Salvar no arquivo	
		total = totalReceita - totalDespesa;
		fprintf(fp, "TOTAL RECEITA:%.2f",totalReceita);	
		fprintf(fp, "\tTOTAL DESPESA:%.2f",totalDespesa);	
		fprintf(fp, "\tTOTAL:%.2f\n",total);	
	}
	else if (isExpense(movimento)){
		totalDespesa += lancamento.valor; 
		fprintf(fp,"=================================\n");
		fprintf(fp,"MOVIMENTECAO:Despesa\n");

		// DESCRIÇÃO DO MOVIMENTO
		fprintf(fp, "Data : %s", dateNow());
		fprintf(fp, "\t\tDESCRICAO: %s",lancamento.descricao);
		fprintf(fp, "\t\tVALOR: %.2f\n",lancamento.valor);

		// CALCULA O TOTAL
		// Salvar no arquivo	
		total = totalReceita - totalDespesa;
		fprintf(fp, "TOTAL RECEITA:%.2f",totalReceita);	
		fprintf(fp, "\tTOTAL DESPESA:%.2f",totalDespesa);	
		fprintf(fp, "\tTOTAL:%.2f\n",total);	
	}else if (isExit(movimento)){	
		total = totalReceita - totalDespesa;
		fprintf(fp,"==============\n",total);	
		fprintf(fp,"TOTAL:%.2f\n",total);	
		fprintf(fp,"==============\n",total);	
		fclose(fp);
		exit(EXIT_SUCCESS);
	}

	fclose(fp);	
}