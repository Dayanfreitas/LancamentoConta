#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/display.h"

#define  NOME_ARQUIVO "financial_movement.txt"
#define  MODO_ARQUIVO "a"

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
void searchDate();
void showDate();

void pause();
void clean();

void readIncoming();
void readExpense();

void saveMovement(int movimento, FILE *fp);

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

void searchDate(){
	time_t mytime;
	mytime = time(NULL);
	struct tm tm = *localtime(&mytime);
	
	lancamento.data.dia = tm.tm_mday;
	lancamento.data.mes = tm.tm_mon + 1;
	lancamento.data.ano = tm.tm_year + 1900;	
}

void showDate(){
	searchDate();
	printf("Data: %d/%d/%d\n", lancamento.data.dia, lancamento.data.mes, lancamento.data.ano);
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



void saveMovement(int movimento, FILE *fp) {
	int movimentoReceita = 1;
	int movimentoDespesa = 2;
	int sair = 0;
	float static totalReceita = 0;
	float static totalDespesa = 0;
	float static total = 0;
	
	fp = fopen (NOME_ARQUIVO, MODO_ARQUIVO);

	if(movimento == movimentoReceita){
		totalReceita += lancamento.valor; 
		fprintf(fp,"=================================\n");
		fprintf(fp,"MOVIMENTECAO:Receita\n");        
	}
	else if (movimento == movimentoDespesa){
		totalDespesa += lancamento.valor; 
		fprintf(fp,"=================================\n");
		fprintf(fp,"MOVIMENTECAO:Despesa\n");
	}else if ( movimento == sair ){	
		total = totalReceita - totalDespesa;
		fprintf(fp,"==============\n",total);	
		fprintf(fp,"TOTAL:%.2f\n",total);	
		fprintf(fp,"==============\n",total);	
		fclose(fp);
		exit(0);
	}

	showDate();

	fprintf(fp,"Data :%d/%d/%d",lancamento.data.dia,lancamento.data.mes,lancamento.data.ano);
	fprintf(fp,"\t\tDESCRICAO: %s",lancamento.descricao);
	fprintf(fp,"\t\tVALOR: %.2f\n",lancamento.valor);

	total = totalReceita - totalDespesa;
	fprintf(fp,"TOTAL RECEITA:%.2f",totalReceita);	
	fprintf(fp,"\tTOTAL DESPESA:%.2f",totalDespesa);	
	fprintf(fp,"\tTOTAL:%.2f\n",total);	

	fclose(fp);	
}