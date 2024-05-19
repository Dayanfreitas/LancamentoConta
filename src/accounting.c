#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/display.h"
#include "../include/date_utils.h"

#define  NOME_ARQUIVO "financial_movement.txt"
#define  MODO_ARQUIVO "a"

#define OP_INCOMING 1
#define OP_EXPENSE 2
	
// Definição de uma macro para limpar a tela, dependendo do sistema operacional
#ifdef _WIN32
	#define CLEAR_SCREEN "cls"
#else
	#define CLEAR_SCREEN "clear"
#endif

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

void pause();
void clean();

void readIncoming();
void readExpense();

void saveMovement(int movimento, FILE *fp);

int isIncoming(int opc);
int isExpense(int opc);
int isExit(int opc);

int main(){
	accountant();
	return 0;
}

void accountant(){
	FILE *fp;
	char choice[10];	
	int opc;
	
	pause();
	showOptions();
	fgets(choice, sizeof(choice), stdin);
	opc = atoi(choice);

	clean();
	switch(opc) {
		case 1:
			displayIncoming();
			readIncoming();
			saveMovement(opc, fp);
			break;
		case 2:
			displayExpense();
			readExpense();
			saveMovement(opc, fp);
			break;
		case 3:
			displayMovement();
			fp = fopen(NOME_ARQUIVO, "r");
			int c;

			while (!feof(fp)) {
				c = fgetc(fp);
				printf("%c",c);
			}

			fclose(fp);
			printf("%c\n", c);
			pause();
			break;
		case 0:
			saveMovement(opc, fp);
		default:
			printf("Opção inválida!\n");
			pause();
	}

	fflush(stdin);
	accountant();
}

void pause() {
	printf("\nPressione qualquer tecla para continuar...");
	getchar();
}

void clean(){
	system(CLEAR_SCREEN);
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

int isExit(int opc) {
	return opc == EXIT_SUCCESS;
}

void saveMovement(int movimento, FILE *fp) {
	float static totalReceita = 0;
	float static totalDespesa = 0;
	float static total = 0;
	
	fp = fopen (NOME_ARQUIVO, MODO_ARQUIVO);

	if(isIncoming(movimento)){
		totalReceita += lancamento.valor; 
		fprintf(fp,"=================================\n");
		fprintf(fp,"MOVIMENTECAO:Receita\n");        
	}
	else if (isExpense(movimento)){
		totalDespesa += lancamento.valor; 
		fprintf(fp,"=================================\n");
		fprintf(fp,"MOVIMENTECAO:Despesa\n");
	}else if (isExit(movimento)){	
		total = totalReceita - totalDespesa;
		fprintf(fp,"==============\n",total);	
		fprintf(fp,"TOTAL:%.2f\n",total);	
		fprintf(fp,"==============\n",total);	
		fclose(fp);
		exit(EXIT_SUCCESS);
	}

	fprintf(fp,"Data : %s", dateNow());
	fprintf(fp,"\t\tDESCRICAO: %s",lancamento.descricao);
	fprintf(fp,"\t\tVALOR: %.2f\n",lancamento.valor);

	total = totalReceita - totalDespesa;
	fprintf(fp,"TOTAL RECEITA:%.2f",totalReceita);	
	fprintf(fp,"\tTOTAL DESPESA:%.2f",totalDespesa);	
	fprintf(fp,"\tTOTAL:%.2f\n",total);	

	fclose(fp);	
}