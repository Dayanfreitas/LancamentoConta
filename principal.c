#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define  NOME_ARQUIVO "movimentacao.txt"
#define  MODO_ARQUIVO "a"

typedef struct {
	int dia;
	int mes;
    int ano; 
}date; 
struct ficha_de_conta{
	date data;
 	char descricao[100];  
	float valor;
};
struct ficha_de_conta lancamento;

void limpar();
void exibirMenu();
void buscarData();
void mostrarData();
void cadastrarReceita();
void cadastrarDispesa();
void salvarMovimento(int movimento,FILE *fp);

int main(){
	exibirMenu();
	return 0;
}

void exibirMenu(){
    FILE *fp;
	char opcao[10];
	int opc;
	
	limpar();
	printf("***************************\n");
	mostrarData();
	printf("***************************\n");	
	printf("************MENU***********\n");
  	printf("***************************\n");
  	printf("Insira a opcao desejada\n\n");
	printf("1 - Cadastrar nova Receita(Ganhos)\n");
	printf("2 - Cadastrar nova Despesa(Gastos)\n");
	printf("3 - Listagem de Registros\n");
    printf(">>>");

	gets(opcao);
	opc = atoi(opcao);
	limpar();
	switch(opc){
        case 1:
     		printf("1 - Cadastrar nova Receita(Ganhos)\n");
     		cadastrarReceita();
			salvarMovimento(opc, fp);
			break;
		case 2:
			printf("2 - Cadastrar nova Despesa(Gastos)\n");
			cadastrarDispesa();
			salvarMovimento(opc, fp);
			break;
		case 3:
			printf("3 - Listagem de Registros\n");
			fp = fopen(NOME_ARQUIVO, "r");
			int c;
            while (!feof(fp))
            {
                c = fgetc(fp);
                printf("%c",c);
            }
            fclose(fp);
            printf("%c\n",c);
            system("pause");
			break;
		default:
			printf("Opcao ivalida!\n");
			system("pause");
	}
	fflush(stdin);
	exibirMenu();
}

void limpar(){
	system("cls");
}
void buscarData(){
	time_t mytime;
	mytime = time(NULL);
	struct tm tm = *localtime(&mytime);
	
	lancamento.data.dia = tm.tm_mday;
	lancamento.data.mes = tm.tm_mon + 1;
	lancamento.data.ano = tm.tm_year + 1900;
	
}
void mostrarData(){
	buscarData();
	printf("Data: %d/%d/%d\n", lancamento.data.dia,lancamento.data.mes,lancamento.data.ano);
}
void cadastrarReceita(){
	printf("=========================\n");
	printf("===Cadastro de receita===\n");
	printf("=========================\n");
	printf("\n");
	printf("Digite a descricao:");
	scanf("%s",lancamento.descricao);
    // fgets(receita.descricao, sizeof(90), stdin);
	fflush(stdin);
	printf("Digite o valor:");
	scanf("%f",&lancamento.valor);
}

void cadastrarDispesa(){
	printf("=========================\n");
	printf("===Cadastro de despesa===\n");
	printf("=========================\n");
	printf("\n");
	printf("Digite a descricao:");
	scanf("%s",lancamento.descricao);
	fflush(stdin);
	printf("Digite o valor:");
	scanf("%f",&lancamento.valor);
}
void salvarMovimento(int movimento,FILE *fp) {
	int movimentoReceita = 1;
	int movimentoDespesa = 2;
	float static totalReceita = 0;
	float static totalDespesa = 0;
	printf("Salvar movimento %d!\n",movimento);
	system("pause");
	fp = fopen (NOME_ARQUIVO, MODO_ARQUIVO);

	if(movimento == movimentoReceita){
		totalReceita += lancamento.valor; 
		fprintf(fp,"=================================\n");
		fprintf(fp,"MOVIMENTECAO:Receita\n");        
		printf("TOTAL RECEITA: %f",totalReceita);    	
		system("pause");
	}
	else if (movimento == movimentoDespesa){
		totalDespesa += lancamento.valor; 
		fprintf(fp,"=================================\n");
		fprintf(fp,"MOVIMENTECAO:Despesa\n");
		printf("TOTAL DESPESA: %f",totalDespesa);
		system("pause");

	}
	fprintf(fp,"Data :%d/%d/%d",lancamento.data.dia,lancamento.data.mes,lancamento.data.ano);
	fprintf(fp,"\t\tDESCRICAO: %s",lancamento.descricao);
	fprintf(fp,"\t\tVALOR: %.2f\n",lancamento.valor);	
	fclose(fp);	
}